target_sources(pomdog_static PRIVATE
    # NOTE: RenderSystem
    ${POMDOG_SRC_DIR}/RenderSystem/BufferBindMode.hpp
    ${POMDOG_SRC_DIR}/RenderSystem/BufferHelper.cpp
    ${POMDOG_SRC_DIR}/RenderSystem/BufferHelper.hpp
    ${POMDOG_SRC_DIR}/RenderSystem/GraphicsCapabilities.hpp
    ${POMDOG_SRC_DIR}/RenderSystem/GraphicsCommandListImmediate.cpp
    ${POMDOG_SRC_DIR}/RenderSystem/GraphicsCommandListImmediate.hpp
    ${POMDOG_SRC_DIR}/RenderSystem/GraphicsCommandQueueImmediate.cpp
    ${POMDOG_SRC_DIR}/RenderSystem/GraphicsCommandQueueImmediate.hpp
    ${POMDOG_SRC_DIR}/RenderSystem/NativeBuffer.hpp
    ${POMDOG_SRC_DIR}/RenderSystem/NativeEffectReflection.hpp
    ${POMDOG_SRC_DIR}/RenderSystem/NativeGraphicsCommandList.hpp
    ${POMDOG_SRC_DIR}/RenderSystem/NativeGraphicsCommandQueue.hpp
    ${POMDOG_SRC_DIR}/RenderSystem/NativeGraphicsContext.hpp
    ${POMDOG_SRC_DIR}/RenderSystem/NativeGraphicsDevice.hpp
    ${POMDOG_SRC_DIR}/RenderSystem/NativePipelineState.hpp
    ${POMDOG_SRC_DIR}/RenderSystem/NativeRenderTarget2D.hpp
    ${POMDOG_SRC_DIR}/RenderSystem/NativeSamplerState.hpp
    ${POMDOG_SRC_DIR}/RenderSystem/NativeTexture2D.hpp
    ${POMDOG_SRC_DIR}/RenderSystem/ShaderBytecode.hpp
    ${POMDOG_SRC_DIR}/RenderSystem/ShaderCompileOptions.hpp
    ${POMDOG_SRC_DIR}/RenderSystem/SurfaceFormatHelper.cpp
    ${POMDOG_SRC_DIR}/RenderSystem/SurfaceFormatHelper.hpp
    ${POMDOG_SRC_DIR}/RenderSystem/TextureHelper.cpp
    ${POMDOG_SRC_DIR}/RenderSystem/TextureHelper.hpp

    $<$<AND:$<PLATFORM_ID:Windows,Linux,Darwin>,$<BOOL:${POMDOG_USE_GL4}>>:
        # NOTE: RenderSystem.GL4
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/BlendStateGL4.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/BlendStateGL4.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/BufferGL4.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/BufferGL4.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/DepthStencilStateGL4.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/DepthStencilStateGL4.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/EffectReflectionGL4.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/EffectReflectionGL4.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/ErrorChecker.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/ErrorChecker.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/FormatHelper.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/FormatHelper.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/GraphicsContextGL4.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/GraphicsContextGL4.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/GraphicsDeviceGL4.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/GraphicsDeviceGL4.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/InputLayoutGL4.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/InputLayoutGL4.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/OpenGLContext.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/OpenGLPrerequisites.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/PipelineStateGL4.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/PipelineStateGL4.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/RasterizerStateGL4.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/RasterizerStateGL4.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/RenderTarget2DGL4.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/RenderTarget2DGL4.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/SamplerStateGL4.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/SamplerStateGL4.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/ShaderGL4.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/ShaderGL4.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/Texture2DGL4.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/Texture2DGL4.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/TypesafeGL4.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/TypesafeHelperGL4.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.GL4/VertexBufferBindingGL4.hpp
    >

    $<$<PLATFORM_ID:Windows>:
        # NOTE: RenderSystem.DXGI
        ${POMDOG_SRC_DIR}/RenderSystem.DXGI/DXGIFormatHelper.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.DXGI/DXGIFormatHelper.hpp
    >

    $<$<PLATFORM_ID:Windows>:
        # NOTE: RenderSystem.Direct3D
        ${POMDOG_SRC_DIR}/RenderSystem.Direct3D/HLSLCompiling.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.Direct3D/HLSLCompiling.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Direct3D/HLSLReflectionHelper.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.Direct3D/HLSLReflectionHelper.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Direct3D/PrerequisitesDirect3D.hpp
    >

    $<$<PLATFORM_ID:Windows>:
        # NOTE: RenderSystem.Direct3D11
        ${POMDOG_SRC_DIR}/RenderSystem.Direct3D11/BufferDirect3D11.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.Direct3D11/BufferDirect3D11.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Direct3D11/EffectReflectionDirect3D11.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.Direct3D11/EffectReflectionDirect3D11.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Direct3D11/FormatHelper.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.Direct3D11/FormatHelper.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Direct3D11/GraphicsContextDirect3D11.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.Direct3D11/GraphicsContextDirect3D11.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Direct3D11/GraphicsDeviceDirect3D11.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.Direct3D11/GraphicsDeviceDirect3D11.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Direct3D11/PipelineStateDirect3D11.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.Direct3D11/PipelineStateDirect3D11.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Direct3D11/PrerequisitesDirect3D11.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Direct3D11/RenderTarget2DDirect3D11.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.Direct3D11/RenderTarget2DDirect3D11.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Direct3D11/SamplerStateDirect3D11.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.Direct3D11/SamplerStateDirect3D11.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Direct3D11/ShaderDirect3D11.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.Direct3D11/ShaderDirect3D11.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Direct3D11/Texture2DDirect3D11.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.Direct3D11/Texture2DDirect3D11.hpp
    >

    $<$<PLATFORM_ID:Darwin>:
        # NOTE: RenderSystem.Metal
        ${POMDOG_SRC_DIR}/RenderSystem.Metal/BufferMetal.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Metal/BufferMetal.mm
        ${POMDOG_SRC_DIR}/RenderSystem.Metal/ConstantsMetal.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Metal/EffectReflectionMetal.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Metal/EffectReflectionMetal.mm
        ${POMDOG_SRC_DIR}/RenderSystem.Metal/GraphicsContextMetal.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Metal/GraphicsContextMetal.mm
        ${POMDOG_SRC_DIR}/RenderSystem.Metal/GraphicsDeviceMetal.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Metal/GraphicsDeviceMetal.mm
        ${POMDOG_SRC_DIR}/RenderSystem.Metal/MetalFormatHelper.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Metal/MetalFormatHelper.mm
        ${POMDOG_SRC_DIR}/RenderSystem.Metal/PipelineStateMetal.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Metal/PipelineStateMetal.mm
        ${POMDOG_SRC_DIR}/RenderSystem.Metal/RenderTarget2DMetal.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Metal/RenderTarget2DMetal.mm
        ${POMDOG_SRC_DIR}/RenderSystem.Metal/SamplerStateMetal.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Metal/SamplerStateMetal.mm
        ${POMDOG_SRC_DIR}/RenderSystem.Metal/ShaderMetal.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Metal/ShaderMetal.mm
        ${POMDOG_SRC_DIR}/RenderSystem.Metal/Texture2DMetal.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Metal/Texture2DMetal.mm
    >

    $<$<BOOL:${POMDOG_USE_VULKAN}>:
        # NOTE: RenderSystem.Vulkan
        ${POMDOG_SRC_DIR}/RenderSystem.Vulkan/BufferVulkan.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.Vulkan/BufferVulkan.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Vulkan/EffectReflectionVulkan.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.Vulkan/EffectReflectionVulkan.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Vulkan/FormatHelper.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.Vulkan/FormatHelper.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Vulkan/GraphicsCommandListVulkan.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.Vulkan/GraphicsCommandListVulkan.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Vulkan/GraphicsCommandQueueVulkan.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.Vulkan/GraphicsCommandQueueVulkan.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Vulkan/GraphicsDeviceVulkan.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.Vulkan/GraphicsDeviceVulkan.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Vulkan/PipelineStateVulkan.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.Vulkan/PipelineStateVulkan.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Vulkan/RenderTarget2DVulkan.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.Vulkan/RenderTarget2DVulkan.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Vulkan/SamplerStateVulkan.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.Vulkan/SamplerStateVulkan.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Vulkan/ShaderVulkan.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.Vulkan/ShaderVulkan.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Vulkan/Texture2DVulkan.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.Vulkan/Texture2DVulkan.hpp
        ${POMDOG_SRC_DIR}/RenderSystem.Vulkan/VulkanFormatHelper.cpp
        ${POMDOG_SRC_DIR}/RenderSystem.Vulkan/VulkanFormatHelper.hpp
    >
)
