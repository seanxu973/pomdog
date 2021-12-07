// Copyright (c) 2013-2021 mogemimi. Distributed under the MIT license.

#include "pomdog/graphics/gl4/buffer_gl4.hpp"
#include "pomdog/basic/conditional_compilation.hpp"
#include "pomdog/basic/unreachable.hpp"
#include "pomdog/graphics/buffer_usage.hpp"
#include "pomdog/graphics/gl4/error_checker.hpp"
#include "pomdog/graphics/gl4/typesafe_helper_gl4.hpp"
#include "pomdog/utility/assert.hpp"
#include "pomdog/utility/scope_guard.hpp"

POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_BEGIN
#include <utility>
POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_END

namespace Pomdog::Detail::GL4 {
namespace {

GLenum ToBufferUsage(BufferUsage bufferUsage) noexcept
{
    switch (bufferUsage) {
    case BufferUsage::Dynamic:
        return GL_DYNAMIC_DRAW;
    case BufferUsage::Immutable:
        return GL_STATIC_DRAW;
    }
    POMDOG_UNREACHABLE("Unsupported buffer usage");
}

template <class Tag>
struct BufferTraits;

template <>
struct BufferTraits<ConstantBuffer> {
    constexpr static GLenum Buffer = GL_UNIFORM_BUFFER;
};

template <>
struct BufferTraits<IndexBuffer> {
    constexpr static GLenum Buffer = GL_ELEMENT_ARRAY_BUFFER;
};

template <>
struct BufferTraits<VertexBuffer> {
    constexpr static GLenum Buffer = GL_ARRAY_BUFFER;
};

} // namespace

template <>
struct TypesafeHelperGL4::Traits<BufferObjectGL4<ConstantBuffer>> {
    constexpr static GLenum BufferBinding = GL_UNIFORM_BUFFER_BINDING;
    constexpr static GLenum BufferTarget = BufferTraits<ConstantBuffer>::Buffer;
};

template <>
struct TypesafeHelperGL4::Traits<BufferObjectGL4<IndexBuffer>> {
    constexpr static GLenum BufferBinding = GL_ELEMENT_ARRAY_BUFFER_BINDING;
    constexpr static GLenum BufferTarget = BufferTraits<IndexBuffer>::Buffer;
};

template <>
struct TypesafeHelperGL4::Traits<BufferObjectGL4<VertexBuffer>> {
    constexpr static GLenum BufferBinding = GL_ARRAY_BUFFER_BINDING;
    constexpr static GLenum BufferTarget = BufferTraits<VertexBuffer>::Buffer;
};

template <class Tag>
std::unique_ptr<Error>
BufferGL4<Tag>::Initialize(std::size_t sizeInBytes, BufferUsage bufferUsage) noexcept
{
    POMDOG_ASSERT(bufferUsage != BufferUsage::Immutable);
    return Initialize(nullptr, sizeInBytes, bufferUsage);
}

template <class Tag>
std::unique_ptr<Error>
BufferGL4<Tag>::Initialize(
    const void* sourceData,
    std::size_t sizeInBytes,
    BufferUsage bufferUsage) noexcept
{
    POMDOG_ASSERT(bufferUsage == BufferUsage::Immutable
            ? sourceData != nullptr
            : true);

    // Generate new buffer
    bufferObject = ([] {
        BufferObject buffer;
        glGenBuffers(1, buffer.Data());
        return buffer;
    })();
    POMDOG_CHECK_ERROR_GL4("glGenBuffers");

    auto const oldBuffer = TypesafeHelperGL4::Get<BufferObject>();
    ScopeGuard scope([&] { TypesafeHelperGL4::BindBuffer(oldBuffer); });

    POMDOG_ASSERT(bufferObject);
    TypesafeHelperGL4::BindBuffer(*bufferObject);
    POMDOG_CHECK_ERROR_GL4("glBindBuffer");

    POMDOG_ASSERT(sizeInBytes > 0);
    glBufferData(BufferTraits<Tag>::Buffer,
        sizeInBytes,
        sourceData,
        ToBufferUsage(bufferUsage));
    POMDOG_CHECK_ERROR_GL4("glBufferData");

    return nullptr;
}

template <class Tag>
BufferGL4<Tag>::~BufferGL4()
{
    if (bufferObject) {
        glDeleteBuffers(1, bufferObject->Data());
        POMDOG_CHECK_ERROR_GL4("glDeleteBuffers");
    }
}

template <class Tag>
void BufferGL4<Tag>::GetData(
    std::size_t offsetInBytes,
    void* destination,
    std::size_t sizeInBytes) const
{
    POMDOG_ASSERT(destination != nullptr);
    POMDOG_ASSERT(sizeInBytes > 0);

    auto const oldBuffer = TypesafeHelperGL4::Get<BufferObject>();
    ScopeGuard scope([&] { TypesafeHelperGL4::BindBuffer(oldBuffer); });

    POMDOG_ASSERT(bufferObject);
    TypesafeHelperGL4::BindBuffer(*bufferObject);
    POMDOG_CHECK_ERROR_GL4("glBindBuffer");

#if defined(DEBUG) && !defined(NDEBUG)
    {
        GLint bufferSize = 0;
        glGetBufferParameteriv(BufferTraits<Tag>::Buffer,
            GL_BUFFER_SIZE, &bufferSize);
        POMDOG_ASSERT((offsetInBytes + sizeInBytes) <= static_cast<std::size_t>(bufferSize));
    }
#endif

    glGetBufferSubData(BufferTraits<Tag>::Buffer,
        offsetInBytes, sizeInBytes, destination);
    POMDOG_CHECK_ERROR_GL4("glGetBufferSubData");
}

template <class Tag>
void BufferGL4<Tag>::SetData(
    std::size_t offsetInBytes,
    const void* source,
    std::size_t sizeInBytes)
{
    POMDOG_ASSERT(source != nullptr);

    auto const oldBuffer = TypesafeHelperGL4::Get<BufferObject>();
    ScopeGuard scope([&] { TypesafeHelperGL4::BindBuffer(oldBuffer); });

    POMDOG_ASSERT(bufferObject);
    TypesafeHelperGL4::BindBuffer(*bufferObject);
    POMDOG_CHECK_ERROR_GL4("glBindBuffer");

#if defined(DEBUG) && !defined(NDEBUG)
    {
        GLint bufferSize = 0;
        glGetBufferParameteriv(BufferTraits<Tag>::Buffer,
            GL_BUFFER_SIZE, &bufferSize);
        POMDOG_ASSERT(sizeInBytes <= static_cast<std::size_t>(bufferSize));
    }
#endif

    POMDOG_ASSERT(sizeInBytes > 0);
    glBufferSubData(BufferTraits<Tag>::Buffer,
        offsetInBytes, sizeInBytes, source);
    POMDOG_CHECK_ERROR_GL4("glBufferSubData");
}

template <class Tag>
void BufferGL4<Tag>::BindBuffer()
{
    POMDOG_ASSERT(bufferObject);
    TypesafeHelperGL4::BindBuffer(*bufferObject);
    POMDOG_CHECK_ERROR_GL4("glBindBuffer");
}

template <class Tag>
GLuint BufferGL4<Tag>::GetBuffer() const
{
    POMDOG_ASSERT(bufferObject);
    return bufferObject->value;
}

// explicit instantiations
template class BufferGL4<ConstantBuffer>;
template class BufferGL4<IndexBuffer>;
template class BufferGL4<VertexBuffer>;

} // namespace Pomdog::Detail::GL4