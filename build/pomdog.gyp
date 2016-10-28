{
  'includes': ['common.gypi'],
  'conditions': [
    ['OS == "win"', {
      'variables': {
        'application_platform%': 'Win32',
        'renderers%': ['Direct3D11', 'GL4'],
        'audio%': 'XAudio2',
        'input_devices%': ['DirectInput'],
      },
    }],
    ['OS == "mac"', {
      'variables': {
        'application_platform%': 'Cocoa',
        'renderers%': ['GL4'],
        'audio%': 'OpenAL',
        'input_devices%': [],
      },
    }],
    ['OS == "ios"', {
      'variables': {
        'application_platform%': 'CocoaTouch',
        'renderers%': ['Metal'],
        'audio%': 'OpenAL',
        'input_devices%': [],
      },
    }],
    ['OS == "linux" or OS == "freebsd" or OS == "openbsd"', {
      'variables': {
        'application_platform%': 'X11',
        'renderers%': ['GL4'],
        'audio%': 'OpenAL',
        'input_devices%': [],
      },
    }],
  ],
  'variables': {
    'pomdog_library_core_sources': [
      '../include/Pomdog/Application/Duration.hpp',
      '../include/Pomdog/Application/Game.hpp',
      '../include/Pomdog/Application/GameClock.hpp',
      '../include/Pomdog/Application/GameHost.hpp',
      '../include/Pomdog/Application/GameWindow.hpp',
      '../include/Pomdog/Application/MouseCursor.hpp',
      '../include/Pomdog/Application/Timer.hpp',
      '../include/Pomdog/Application/TimePoint.hpp',
      '../include/Pomdog/Async/Helpers.hpp',
      '../include/Pomdog/Async/ImmediateScheduler.hpp',
      '../include/Pomdog/Async/QueuedScheduler.hpp',
      '../include/Pomdog/Async/Scheduler.hpp',
      '../include/Pomdog/Async/Task.hpp',
      '../include/Pomdog/Audio/AudioClip.hpp',
      '../include/Pomdog/Audio/AudioChannels.hpp',
      '../include/Pomdog/Audio/AudioEmitter.hpp',
      '../include/Pomdog/Audio/AudioEngine.hpp',
      '../include/Pomdog/Audio/AudioListener.hpp',
      '../include/Pomdog/Audio/SoundEffect.hpp',
      '../include/Pomdog/Audio/SoundState.hpp',
      '../include/Pomdog/Audio/detail/ForwardDeclarations.hpp',
      '../include/Pomdog/Basic/Export.hpp',
      '../include/Pomdog/Basic/Platform.hpp',
      '../include/Pomdog/Basic/Version.hpp',
      '../include/Pomdog/Content/AssetManager.hpp',
      '../include/Pomdog/Content/AssetBuilders/Builder.hpp',
      '../include/Pomdog/Content/AssetBuilders/PipelineStateBuilder.hpp',
      '../include/Pomdog/Content/AssetBuilders/ShaderBuilder.hpp',
      '../include/Pomdog/Content/Utility/BinaryFileStream.hpp',
      '../include/Pomdog/Content/Utility/BinaryReader.hpp',
      '../include/Pomdog/Content/Utility/MakeFourCC.hpp',
      '../include/Pomdog/Content/detail/AssetDictionary.hpp',
      '../include/Pomdog/Content/detail/AssetLoaderContext.hpp',
      '../include/Pomdog/Content/detail/AssetLoader.hpp',
      '../include/Pomdog/Content/detail/AssetLoaders/AudioClipLoader.hpp',
      '../include/Pomdog/Content/detail/AssetLoaders/Texture2DLoader.hpp',
      '../include/Pomdog/Graphics/Blend.hpp',
      '../include/Pomdog/Graphics/BlendDescription.hpp',
      '../include/Pomdog/Graphics/BlendOperation.hpp',
      '../include/Pomdog/Graphics/BufferUsage.hpp',
      '../include/Pomdog/Graphics/ComparisonFunction.hpp',
      '../include/Pomdog/Graphics/ConstantBuffer.hpp',
      '../include/Pomdog/Graphics/CullMode.hpp',
      '../include/Pomdog/Graphics/DepthFormat.hpp',
      '../include/Pomdog/Graphics/DepthStencilDescription.hpp',
      '../include/Pomdog/Graphics/DepthStencilOperation.hpp',
      '../include/Pomdog/Graphics/EffectAnnotation.hpp',
      '../include/Pomdog/Graphics/EffectConstantDescription.hpp',
      '../include/Pomdog/Graphics/EffectReflection.hpp',
      '../include/Pomdog/Graphics/EffectVariableClass.hpp',
      '../include/Pomdog/Graphics/EffectVariableType.hpp',
      '../include/Pomdog/Graphics/EffectVariable.hpp',
      '../include/Pomdog/Graphics/FillMode.hpp',
      '../include/Pomdog/Graphics/GraphicsCommandList.hpp',
      '../include/Pomdog/Graphics/GraphicsCommandQueue.hpp',
      '../include/Pomdog/Graphics/GraphicsDevice.hpp',
      '../include/Pomdog/Graphics/IndexBuffer.hpp',
      '../include/Pomdog/Graphics/IndexElementSize.hpp',
      '../include/Pomdog/Graphics/InputClassification.hpp',
      '../include/Pomdog/Graphics/InputElement.hpp',
      '../include/Pomdog/Graphics/InputElementFormat.hpp',
      '../include/Pomdog/Graphics/InputLayoutDescription.hpp',
      '../include/Pomdog/Graphics/InputLayoutHelper.hpp',
      '../include/Pomdog/Graphics/PipelineState.hpp',
      '../include/Pomdog/Graphics/PipelineStateDescription.hpp',
      '../include/Pomdog/Graphics/PresentationParameters.hpp',
      '../include/Pomdog/Graphics/PrimitiveTopology.hpp',
      '../include/Pomdog/Graphics/RasterizerDescription.hpp',
      '../include/Pomdog/Graphics/RenderPass.hpp',
      '../include/Pomdog/Graphics/RenderTarget2D.hpp',
      '../include/Pomdog/Graphics/RenderTargetBlendDescription.hpp',
      '../include/Pomdog/Graphics/SamplerDescription.hpp',
      '../include/Pomdog/Graphics/SamplerState.hpp',
      '../include/Pomdog/Graphics/Shader.hpp',
      '../include/Pomdog/Graphics/ShaderLanguage.hpp',
      '../include/Pomdog/Graphics/ShaderPipelineStage.hpp',
      '../include/Pomdog/Graphics/SurfaceFormat.hpp',
      '../include/Pomdog/Graphics/StencilOperation.hpp',
      '../include/Pomdog/Graphics/Texture.hpp',
      '../include/Pomdog/Graphics/Texture2D.hpp',
      '../include/Pomdog/Graphics/TextureAddressMode.hpp',
      '../include/Pomdog/Graphics/TextureFilter.hpp',
      '../include/Pomdog/Graphics/VertexBuffer.hpp',
      '../include/Pomdog/Graphics/VertexBufferBinding.hpp',
      '../include/Pomdog/Graphics/Viewport.hpp',
      '../include/Pomdog/Graphics/detail/ForwardDeclarations.hpp',
      '../include/Pomdog/Graphics/detail/EffectBinaryParameter.hpp',
      '../include/Pomdog/Graphics/ShaderCompilers/GLSLCompiler.hpp',
      '../include/Pomdog/Graphics/ShaderCompilers/HLSLCompiler.hpp',
      '../include/Pomdog/Graphics/ShaderCompilers/MetalCompiler.hpp',
      '../include/Pomdog/Input/ButtonState.hpp',
      '../include/Pomdog/Input/Gamepad.hpp',
      '../include/Pomdog/Input/GamepadButtons.hpp',
      '../include/Pomdog/Input/GamepadCapabilities.hpp',
      '../include/Pomdog/Input/GamepadDPad.hpp',
      '../include/Pomdog/Input/GamepadState.hpp',
      '../include/Pomdog/Input/GamepadThumbSticks.hpp',
      '../include/Pomdog/Input/GamepadType.hpp',
      '../include/Pomdog/Input/Keyboard.hpp',
      '../include/Pomdog/Input/KeyboardState.hpp',
      '../include/Pomdog/Input/KeyState.hpp',
      '../include/Pomdog/Input/Keys.hpp',
      '../include/Pomdog/Input/Mouse.hpp',
      '../include/Pomdog/Input/MouseState.hpp',
      '../include/Pomdog/Input/PlayerIndex.hpp',
      '../include/Pomdog/Input/TouchLocation.hpp',
      '../include/Pomdog/Input/TouchLocationState.hpp',
      '../include/Pomdog/Logging/Log.hpp',
      '../include/Pomdog/Logging/LogChannel.hpp',
      '../include/Pomdog/Logging/LogEntry.hpp',
      '../include/Pomdog/Logging/LogLevel.hpp',
      '../include/Pomdog/Math/BoundingBox.hpp',
      '../include/Pomdog/Math/BoundingBox2D.hpp',
      '../include/Pomdog/Math/BoundingCircle.hpp',
      '../include/Pomdog/Math/BoundingSphere.hpp',
      '../include/Pomdog/Math/Color.hpp',
      '../include/Pomdog/Math/ContainmentType.hpp',
      '../include/Pomdog/Math/Degree.hpp',
      '../include/Pomdog/Math/MathHelper.hpp',
      '../include/Pomdog/Math/Matrix2x2.hpp',
      '../include/Pomdog/Math/Matrix3x2.hpp',
      '../include/Pomdog/Math/Matrix3x3.hpp',
      '../include/Pomdog/Math/Matrix4x4.hpp',
      '../include/Pomdog/Math/Point2D.hpp',
      '../include/Pomdog/Math/Point3D.hpp',
      '../include/Pomdog/Math/Quaternion.hpp',
      '../include/Pomdog/Math/Radian.hpp',
      '../include/Pomdog/Math/Ray.hpp',
      '../include/Pomdog/Math/Rectangle.hpp',
      '../include/Pomdog/Math/Vector2.hpp',
      '../include/Pomdog/Math/Vector3.hpp',
      '../include/Pomdog/Math/Vector4.hpp',
      '../include/Pomdog/Math/detail/Coordinate2D.hpp',
      '../include/Pomdog/Math/detail/Coordinate3D.hpp',
      '../include/Pomdog/Math/detail/FloatingPointMatrix2x2.hpp',
      '../include/Pomdog/Math/detail/FloatingPointMatrix3x2.hpp',
      '../include/Pomdog/Math/detail/FloatingPointMatrix3x3.hpp',
      '../include/Pomdog/Math/detail/FloatingPointMatrix4x4.hpp',
      '../include/Pomdog/Math/detail/FloatingPointQuaternion.hpp',
      '../include/Pomdog/Math/detail/FloatingPointVector2.hpp',
      '../include/Pomdog/Math/detail/FloatingPointVector3.hpp',
      '../include/Pomdog/Math/detail/FloatingPointVector4.hpp',
      '../include/Pomdog/Math/detail/ForwardDeclarations.hpp',
      '../include/Pomdog/Math/detail/TaggedArithmetic.hpp',
      '../include/Pomdog/Reactive/Observable.hpp',
      '../include/Pomdog/Reactive/ObservableBase.hpp',
      '../include/Pomdog/Reactive/ObservableBuilder.hpp',
      '../include/Pomdog/Reactive/Observer.hpp',
      '../include/Pomdog/Reactive/Subscriber.hpp',
      '../include/Pomdog/Reactive/Operators/BufferOperator.hpp',
      '../include/Pomdog/Reactive/Operators/DebounceOperator.hpp',
      '../include/Pomdog/Reactive/Operators/DelayOperator.hpp',
      '../include/Pomdog/Reactive/Operators/DistinctOperator.hpp',
      '../include/Pomdog/Reactive/Operators/DoOperator.hpp',
      '../include/Pomdog/Reactive/Operators/FilterOperator.hpp',
      '../include/Pomdog/Reactive/Operators/FirstOperator.hpp',
      '../include/Pomdog/Reactive/Operators/LastOperator.hpp',
      '../include/Pomdog/Reactive/Operators/MapOperator.hpp',
      '../include/Pomdog/Reactive/Operators/MergeOperator.hpp',
      '../include/Pomdog/Reactive/Operators/ScanOperator.hpp',
      '../include/Pomdog/Reactive/Operators/SkipLastOperator.hpp',
      '../include/Pomdog/Reactive/Operators/SkipOperator.hpp',
      '../include/Pomdog/Reactive/Operators/TakeOperator.hpp',
      '../include/Pomdog/Reactive/Operators/TimeoutOperator.hpp',
      '../include/Pomdog/Reactive/Operators/ZipOperator.hpp',
      '../include/Pomdog/Reactive/Subjects/KeyDownSubject.hpp',
      '../include/Pomdog/Signals/Connection.hpp',
      '../include/Pomdog/Signals/ConnectionList.hpp',
      '../include/Pomdog/Signals/Event.hpp',
      '../include/Pomdog/Signals/EventQueue.hpp',
      '../include/Pomdog/Signals/Helpers.hpp',
      '../include/Pomdog/Signals/ScopedConnection.hpp',
      '../include/Pomdog/Signals/Signal.hpp',
      '../include/Pomdog/Signals/detail/EventBody.hpp',
      '../include/Pomdog/Signals/detail/ForwardDeclarations.hpp',
      '../include/Pomdog/Signals/detail/SignalBody.hpp',
      '../include/Pomdog/Utility/Any.hpp',
      '../include/Pomdog/Utility/Assert.hpp',
      '../include/Pomdog/Utility/Exception.hpp',
      '../include/Pomdog/Utility/FileSystem.hpp',
      '../include/Pomdog/Utility/Optional.hpp',
      '../include/Pomdog/Utility/PathHelper.hpp',
      '../include/Pomdog/Utility/StringHelper.hpp',
      '../include/Pomdog/Utility/detail/CRC32.hpp',
      '../include/Pomdog/Utility/detail/Tagged.hpp',
      '../src/Application/GameClock.cpp',
      '../src/Application/SubsystemScheduler.hpp',
      '../src/Application/SystemEvents.hpp',
      '../src/Application/Timer.cpp',
      '../src/Application/TimeSource.hpp',
      '../src/Async/ImmediateScheduler.cpp',
      '../src/Async/QueuedScheduler.cpp',
      '../src/Async/Task.cpp',
      '../src/Audio/AudioClip.cpp',
      '../src/Audio/AudioEngine.cpp',
      '../src/Audio/SoundEffect.cpp',
      '../src/Basic/ConditionalCompilation.hpp',
      '../src/Content/AssetDictionary.cpp',
      '../src/Content/AssetLoaderContext.cpp',
      '../src/Content/AssetManager.cpp',
      '../src/Content/AssetBuilders/PipelineStateBuilder.cpp',
      '../src/Content/AssetBuilders/ShaderBuilder.cpp',
      '../src/Content/AssetLoaders/AudioClipLoader.cpp',
      '../src/Content/AssetLoaders/Texture2DLoader.cpp',
      '../src/Content/Utility/DDSTextureReader.cpp',
      '../src/Content/Utility/DDSTextureReader.hpp',
      '../src/Content/Utility/MSWaveAudioLoader.cpp',
      '../src/Content/Utility/MSWaveAudioLoader.hpp',
      '../src/Content/Utility/PNGTextureReader.cpp',
      '../src/Content/Utility/PNGTextureReader.hpp',
      '../src/Graphics/ConstantBuffer.cpp',
      '../src/Graphics/EffectBinaryParameter.cpp',
      '../src/Graphics/EffectReflection.cpp',
      '../src/Graphics/GraphicsCommandList.cpp',
      '../src/Graphics/GraphicsCommandQueue.cpp',
      '../src/Graphics/GraphicsDevice.cpp',
      '../src/Graphics/IndexBuffer.cpp',
      '../src/Graphics/InputLayoutHelper.cpp',
      '../src/Graphics/PipelineState.cpp',
      '../src/Graphics/RenderTarget2D.cpp',
      '../src/Graphics/SamplerState.cpp',
      '../src/Graphics/Texture2D.cpp',
      '../src/Graphics/Viewport.cpp',
      '../src/Graphics/VertexBuffer.cpp',
      '../src/Graphics/ShaderCompilers/GLSLCompiler.cpp',
      '../src/Graphics/ShaderCompilers/HLSLCompiler.cpp',
      '../src/Graphics/ShaderCompilers/MetalCompiler.cpp',
      '../src/Input/KeyboardState.cpp',
      '../src/InputSystem/InputDeviceCreator.hpp',
      '../src/InputSystem/InputDeviceFactory.cpp',
      '../src/InputSystem/InputDeviceFactory.hpp',
      '../src/Logging/Log.cpp',
      '../src/Logging/LogChannel.cpp',
      '../src/Math/BoundingBox.cpp',
      '../src/Math/BoundingBox2D.cpp',
      '../src/Math/BoundingCircle.cpp',
      '../src/Math/BoundingSphere.cpp',
      '../src/Math/Color.cpp',
      '../src/Math/MathHelper.cpp',
      '../src/Math/Ray.cpp',
      '../src/Math/Rectangle.cpp',
      '../src/Math/detail/Coordinate2D.cpp',
      '../src/Math/detail/Coordinate3D.cpp',
      '../src/Math/detail/FloatingPointMatrix2x2.cpp',
      '../src/Math/detail/FloatingPointMatrix3x2.cpp',
      '../src/Math/detail/FloatingPointMatrix3x3.cpp',
      '../src/Math/detail/FloatingPointMatrix4x4.cpp',
      '../src/Math/detail/FloatingPointQuaternion.cpp',
      '../src/Math/detail/FloatingPointVector2.cpp',
      '../src/Math/detail/FloatingPointVector3.cpp',
      '../src/Math/detail/FloatingPointVector4.cpp',
      '../src/RenderSystem/BufferHelper.cpp',
      '../src/RenderSystem/BufferHelper.hpp',
      '../src/RenderSystem/GraphicsCapabilities.hpp',
      '../src/RenderSystem/GraphicsCommandListImmediate.cpp',
      '../src/RenderSystem/GraphicsCommandListImmediate.hpp',
      '../src/RenderSystem/GraphicsCommandQueueImmediate.cpp',
      '../src/RenderSystem/GraphicsCommandQueueImmediate.hpp',
      '../src/RenderSystem/NativeBuffer.hpp',
      '../src/RenderSystem/NativeEffectReflection.hpp',
      '../src/RenderSystem/NativeGraphicsCommandList.hpp',
      '../src/RenderSystem/NativeGraphicsCommandQueue.hpp',
      '../src/RenderSystem/NativeGraphicsContext.hpp',
      '../src/RenderSystem/NativeGraphicsDevice.hpp',
      '../src/RenderSystem/NativePipelineState.hpp',
      '../src/RenderSystem/NativeRenderTarget2D.hpp',
      '../src/RenderSystem/NativeSamplerState.hpp',
      '../src/RenderSystem/NativeTexture2D.hpp',
      '../src/RenderSystem/ShaderBytecode.hpp',
      '../src/RenderSystem/ShaderCompileOptions.hpp',
      '../src/RenderSystem/SurfaceFormatHelper.cpp',
      '../src/RenderSystem/SurfaceFormatHelper.hpp',
      '../src/RenderSystem/TextureHelper.cpp',
      '../src/RenderSystem/TextureHelper.hpp',
      '../src/Signals/Connection.cpp',
      '../src/Signals/ConnectionList.cpp',
      '../src/Signals/EventQueue.cpp',
      '../src/Signals/ScopedConnection.cpp',
      '../src/Utility/AlignedNew.hpp',
      '../src/Utility/CRC32.cpp',
      '../src/Utility/Noncopyable.hpp',
      '../src/Utility/PathHelper.cpp',
      '../src/Utility/ScopeGuard.hpp',
      '../src/Utility/StringHelper.cpp',
    ],
    'pomdog_library_experimental_sources': [
      '../include/Pomdog/Experimental/Graphics/SpriteBatch.hpp',
      '../include/Pomdog/Experimental/Image/GifImage.hpp',
      '../include/Pomdog/Experimental/Image/GifImageLoader.hpp',
      '../include/Pomdog/Experimental/Image/Image.hpp',
      '../include/Pomdog/Experimental/TexturePacker/TextureAtlas.hpp',
      '../include/Pomdog/Experimental/TexturePacker/TextureAtlasGenerator.hpp',
      '../include/Pomdog/Experimental/TexturePacker/TextureAtlasLoader.hpp',
      '../include/Pomdog/Experimental/TexturePacker/TextureRegion.hpp',
      '../src/Experimental/Graphics/SpriteBatch.cpp',
      '../src/Experimental/Image/GifImageLoader.cpp',
      '../src/Experimental/Image/Image.cpp',
      '../src/Experimental/TexturePacker/TextureAtlasGenerator.cpp',
      '../src/Experimental/TexturePacker/TextureAtlasLoader.cpp',
    ],
    'pomdog_library_opengl4_sources': [
      '../src/RenderSystem.GL4/BlendStateGL4.cpp',
      '../src/RenderSystem.GL4/BlendStateGL4.hpp',
      '../src/RenderSystem.GL4/BufferGL4.cpp',
      '../src/RenderSystem.GL4/BufferGL4.hpp',
      '../src/RenderSystem.GL4/DepthStencilStateGL4.cpp',
      '../src/RenderSystem.GL4/DepthStencilStateGL4.hpp',
      '../src/RenderSystem.GL4/EffectReflectionGL4.cpp',
      '../src/RenderSystem.GL4/EffectReflectionGL4.hpp',
      '../src/RenderSystem.GL4/ErrorChecker.cpp',
      '../src/RenderSystem.GL4/ErrorChecker.hpp',
      '../src/RenderSystem.GL4/GraphicsContextGL4.cpp',
      '../src/RenderSystem.GL4/GraphicsContextGL4.hpp',
      '../src/RenderSystem.GL4/GraphicsDeviceGL4.cpp',
      '../src/RenderSystem.GL4/GraphicsDeviceGL4.hpp',
      '../src/RenderSystem.GL4/InputLayoutGL4.cpp',
      '../src/RenderSystem.GL4/InputLayoutGL4.hpp',
      '../src/RenderSystem.GL4/OpenGLContext.hpp',
      '../src/RenderSystem.GL4/OpenGLPrerequisites.hpp',
      '../src/RenderSystem.GL4/PipelineStateGL4.cpp',
      '../src/RenderSystem.GL4/PipelineStateGL4.hpp',
      '../src/RenderSystem.GL4/RasterizerStateGL4.cpp',
      '../src/RenderSystem.GL4/RasterizerStateGL4.hpp',
      '../src/RenderSystem.GL4/RenderTarget2DGL4.cpp',
      '../src/RenderSystem.GL4/RenderTarget2DGL4.hpp',
      '../src/RenderSystem.GL4/SamplerStateGL4.cpp',
      '../src/RenderSystem.GL4/SamplerStateGL4.hpp',
      '../src/RenderSystem.GL4/ShaderGL4.cpp',
      '../src/RenderSystem.GL4/ShaderGL4.hpp',
      '../src/RenderSystem.GL4/Texture2DGL4.cpp',
      '../src/RenderSystem.GL4/Texture2DGL4.hpp',
      '../src/RenderSystem.GL4/TypesafeGL4.hpp',
      '../src/RenderSystem.GL4/TypesafeHelperGL4.hpp',
    ],
    'pomdog_library_metal_sources': [
      '../src/RenderSystem.Metal/BufferMetal.hpp',
      '../src/RenderSystem.Metal/BufferMetal.mm',
      '../src/RenderSystem.Metal/EffectReflectionMetal.hpp',
      '../src/RenderSystem.Metal/EffectReflectionMetal.mm',
      '../src/RenderSystem.Metal/GraphicsContextMetal.hpp',
      '../src/RenderSystem.Metal/GraphicsContextMetal.mm',
      '../src/RenderSystem.Metal/GraphicsDeviceMetal.hpp',
      '../src/RenderSystem.Metal/GraphicsDeviceMetal.mm',
      '../src/RenderSystem.Metal/MetalFormatHelper.hpp',
      '../src/RenderSystem.Metal/MetalFormatHelper.mm',
      '../src/RenderSystem.Metal/PipelineStateMetal.hpp',
      '../src/RenderSystem.Metal/PipelineStateMetal.mm',
      '../src/RenderSystem.Metal/RenderTarget2DMetal.hpp',
      '../src/RenderSystem.Metal/RenderTarget2DMetal.mm',
      '../src/RenderSystem.Metal/SamplerStateMetal.hpp',
      '../src/RenderSystem.Metal/SamplerStateMetal.mm',
      '../src/RenderSystem.Metal/ShaderMetal.hpp',
      '../src/RenderSystem.Metal/ShaderMetal.mm',
      '../src/RenderSystem.Metal/Texture2DMetal.hpp',
      '../src/RenderSystem.Metal/Texture2DMetal.mm',
    ],
    'pomdog_library_vulkan_sources': [
      '../src/RenderSystem.Vulkan/BufferVulkan.cpp',
      '../src/RenderSystem.Vulkan/BufferVulkan.hpp',
      '../src/RenderSystem.Vulkan/EffectReflectionVulkan.cpp',
      '../src/RenderSystem.Vulkan/EffectReflectionVulkan.hpp',
      '../src/RenderSystem.Vulkan/GraphicsCommandListVulkan.cpp',
      '../src/RenderSystem.Vulkan/GraphicsCommandListVulkan.hpp',
      '../src/RenderSystem.Vulkan/GraphicsCommandQueueVulkan.cpp',
      '../src/RenderSystem.Vulkan/GraphicsCommandQueueVulkan.hpp',
      '../src/RenderSystem.Vulkan/GraphicsDeviceVulkan.cpp',
      '../src/RenderSystem.Vulkan/GraphicsDeviceVulkan.hpp',
      '../src/RenderSystem.Vulkan/PipelineStateVulkan.cpp',
      '../src/RenderSystem.Vulkan/PipelineStateVulkan.hpp',
      '../src/RenderSystem.Vulkan/RenderTexture2DVulkan.cpp',
      '../src/RenderSystem.Vulkan/RenderTexture2DVulkan.hpp',
      '../src/RenderSystem.Vulkan/SamplerStateVulkan.cpp',
      '../src/RenderSystem.Vulkan/SamplerStateVulkan.hpp',
      '../src/RenderSystem.Vulkan/ShaderVulkan.cpp',
      '../src/RenderSystem.Vulkan/ShaderVulkan.hpp',
      '../src/RenderSystem.Vulkan/Texture2DVulkan.cpp',
      '../src/RenderSystem.Vulkan/Texture2DVulkan.hpp',
      '../src/RenderSystem.Vulkan/VulkanFormatHelper.cpp',
      '../src/RenderSystem.Vulkan/VulkanFormatHelper.hpp',
    ],
    'pomdog_library_openal_sources': [
      '../src/SoundSystem.OpenAL/AudioClipAL.cpp',
      '../src/SoundSystem.OpenAL/AudioClipAL.hpp',
      '../src/SoundSystem.OpenAL/AudioEngineAL.cpp',
      '../src/SoundSystem.OpenAL/AudioEngineAL.hpp',
      '../src/SoundSystem.OpenAL/ContextOpenAL.cpp',
      '../src/SoundSystem.OpenAL/ContextOpenAL.hpp',
      '../src/SoundSystem.OpenAL/ErrorCheckerAL.cpp',
      '../src/SoundSystem.OpenAL/ErrorCheckerAL.hpp',
      '../src/SoundSystem.OpenAL/PrerequisitesOpenAL.hpp',
      '../src/SoundSystem.OpenAL/SoundEffectAL.cpp',
      '../src/SoundSystem.OpenAL/SoundEffectAL.hpp',
    ],
    'pomdog_library_apple_sources': [
      '../src/Platform.Apple/FileSystemApple.mm',
      '../src/Platform.Apple/TimeSourceApple.cpp',
      '../src/Platform.Apple/TimeSourceApple.hpp',
    ],
    'pomdog_library_cocoa_sources': [
      '../include/Pomdog/Platform/Cocoa/Bootstrap.hpp',
      '../include/Pomdog/Platform/Cocoa/PomdogOpenGLView.hpp',
      '../src/Platform.Cocoa/Bootstrap.mm',
      '../src/Platform.Cocoa/CocoaWindowDelegate.hpp',
      '../src/Platform.Cocoa/CocoaWindowDelegate.mm',
      '../src/Platform.Cocoa/GameHostCocoa.hpp',
      '../src/Platform.Cocoa/GameHostCocoa.mm',
      '../src/Platform.Cocoa/GameWindowCocoa.hpp',
      '../src/Platform.Cocoa/GameWindowCocoa.mm',
      '../src/Platform.Cocoa/KeyboardCocoa.hpp',
      '../src/Platform.Cocoa/KeyboardCocoa.cpp',
      '../src/Platform.Cocoa/MouseCocoa.hpp',
      '../src/Platform.Cocoa/MouseCocoa.cpp',
      '../src/Platform.Cocoa/OpenGLContextCocoa.hpp',
      '../src/Platform.Cocoa/OpenGLContextCocoa.mm',
      '../src/Platform.Cocoa/PomdogOpenGLView.mm',
    ],
    'pomdog_library_dxgi_sources': [
      '../src/RenderSystem.DXGI/DXGIFormatHelper.cpp',
      '../src/RenderSystem.DXGI/DXGIFormatHelper.hpp',
    ],
    'pomdog_library_direct3d_sources': [
      '../src/RenderSystem.Direct3D/HLSLCompiling.cpp',
      '../src/RenderSystem.Direct3D/HLSLCompiling.hpp',
      '../src/RenderSystem.Direct3D/HLSLReflectionHelper.cpp',
      '../src/RenderSystem.Direct3D/HLSLReflectionHelper.hpp',
      '../src/RenderSystem.Direct3D/PrerequisitesDirect3D.hpp',
    ],
    'pomdog_library_direct3d11_sources': [
      '../src/RenderSystem.Direct3D11/BufferDirect3D11.cpp',
      '../src/RenderSystem.Direct3D11/BufferDirect3D11.hpp',
      '../src/RenderSystem.Direct3D11/EffectReflectionDirect3D11.cpp',
      '../src/RenderSystem.Direct3D11/EffectReflectionDirect3D11.hpp',
      '../src/RenderSystem.Direct3D11/GraphicsContextDirect3D11.cpp',
      '../src/RenderSystem.Direct3D11/GraphicsContextDirect3D11.hpp',
      '../src/RenderSystem.Direct3D11/GraphicsDeviceDirect3D11.cpp',
      '../src/RenderSystem.Direct3D11/GraphicsDeviceDirect3D11.hpp',
      '../src/RenderSystem.Direct3D11/PipelineStateDirect3D11.cpp',
      '../src/RenderSystem.Direct3D11/PipelineStateDirect3D11.hpp',
      '../src/RenderSystem.Direct3D11/PrerequisitesDirect3D11.hpp',
      '../src/RenderSystem.Direct3D11/RenderTarget2DDirect3D11.cpp',
      '../src/RenderSystem.Direct3D11/RenderTarget2DDirect3D11.hpp',
      '../src/RenderSystem.Direct3D11/SamplerStateDirect3D11.cpp',
      '../src/RenderSystem.Direct3D11/SamplerStateDirect3D11.hpp',
      '../src/RenderSystem.Direct3D11/ShaderDirect3D11.cpp',
      '../src/RenderSystem.Direct3D11/ShaderDirect3D11.hpp',
      '../src/RenderSystem.Direct3D11/Texture2DDirect3D11.cpp',
      '../src/RenderSystem.Direct3D11/Texture2DDirect3D11.hpp',
    ],
    'pomdog_library_xaudio2_sources': [
      '../src/SoundSystem.XAudio2/AudioClipXAudio2.cpp',
      '../src/SoundSystem.XAudio2/AudioClipXAudio2.hpp',
      '../src/SoundSystem.XAudio2/AudioEngineXAudio2.cpp',
      '../src/SoundSystem.XAudio2/AudioEngineXAudio2.hpp',
      '../src/SoundSystem.XAudio2/PrerequisitesXAudio2.hpp',
      '../src/SoundSystem.XAudio2/SoundEffectXAudio2.cpp',
      '../src/SoundSystem.XAudio2/SoundEffectXAudio2.hpp',
    ],
    'pomdog_library_directinput_sources': [
      '../src/InputSystem.DirectInput/DeviceContextDirectInput.cpp',
      '../src/InputSystem.DirectInput/DeviceContextDirectInput.hpp',
      '../src/InputSystem.DirectInput/PrerequisitesDirectInput.hpp',
    ],
    'pomdog_library_win32_sources': [
      '../include/Pomdog/Platform/Win32/Bootstrap.hpp',
      '../include/Pomdog/Platform/Win32/BootstrapSettingsWin32.hpp',
      '../include/Pomdog/Platform/Win32/PrerequisitesWin32.hpp',
      '../src/Platform.Win32/Bootstrap.cpp',
      '../src/Platform.Win32/GameHostWin32.cpp',
      '../src/Platform.Win32/GameHostWin32.hpp',
      '../src/Platform.Win32/GameWindowWin32.cpp',
      '../src/Platform.Win32/GameWindowWin32.hpp',
      '../src/Platform.Win32/FileSystemWin32.cpp',
      '../src/Platform.Win32/KeyboardWin32.cpp',
      '../src/Platform.Win32/KeyboardWin32.hpp',
      '../src/Platform.Win32/MouseWin32.cpp',
      '../src/Platform.Win32/MouseWin32.hpp',
      '../src/Platform.Win32/TimeSourceWin32.cpp',
      '../src/Platform.Win32/TimeSourceWin32.hpp',
    ],
    'pomdog_library_win32_opengl_sources': [
      '../src/Platform.Win32/OpenGLContextWin32.cpp',
      '../src/Platform.Win32/OpenGLContextWin32.hpp',
    ],
    'pomdog_library_x11_sources': [
      '../include/Pomdog/Platform/X11/Bootstrap.hpp',
      '../src/Platform.X11/Bootstrap.cpp',
      '../src/Platform.X11/GameHostX11.cpp',
      '../src/Platform.X11/GameHostX11.hpp',
      '../src/Platform.X11/GameWindowX11.cpp',
      '../src/Platform.X11/GameWindowX11.hpp',
      '../src/Platform.X11/KeyboardX11.cpp',
      '../src/Platform.X11/KeyboardX11.hpp',
      '../src/Platform.X11/MouseX11.cpp',
      '../src/Platform.X11/MouseX11.hpp',
      '../src/Platform.X11/OpenGLContextX11.cpp',
      '../src/Platform.X11/OpenGLContextX11.hpp',
      '../src/Platform.X11/X11AtomCache.hpp',
      '../src/Platform.X11/X11Context.cpp',
      '../src/Platform.X11/X11Context.hpp',
    ],
    'pomdog_library_linux_sources': [
      '../src/Platform.Linux/FileSystemLinux.cpp',
      '../src/Platform.Linux/TimeSourceLinux.cpp',
      '../src/Platform.Linux/TimeSourceLinux.hpp',
    ],
  },
  'target_defaults': {
    'dependencies': [
      'dependencies/libpng.gyp:libpng_static',
      'dependencies/giflib.gyp:giflib_static',
    ],
    'include_dirs': [
      '../include',
      '../dependencies/libpng',
      '../dependencies/vendor/libpng',
      '../dependencies/vendor/giflib/lib',
    ],
    'sources': [
      '<@(pomdog_library_core_sources)',
      '<@(pomdog_library_experimental_sources)',
      '../include/Pomdog/Pomdog.hpp',
    ],
    'msbuild_settings': {
      'ClCompile': {
        'WarningLevel': 'Level4', # /W4
        'TreatWarningAsError': 'true', # /WX
      },
    },
    'xcode_settings': {
      'GCC_VERSION': 'com.apple.compilers.llvm.clang.1_0',
      'CLANG_CXX_LANGUAGE_STANDARD': 'c++14',
      'CLANG_CXX_LIBRARY': 'libc++',
      # Warnings (Clang):
      'CLANG_WARN_BOOL_CONVERSION': 'YES',
      'CLANG_WARN_CONSTANT_CONVERSION': 'YES',
      'CLANG_WARN_EMPTY_BODY': 'YES',
      'CLANG_WARN_ENUM_CONVERSION': 'YES',
      'CLANG_WARN_INT_CONVERSION': 'YES',
      'CLANG_WARN_UNREACHABLE_CODE': 'YES',
      # Warnings (GCC and Clang):
      'GCC_WARN_64_TO_32_BIT_CONVERSION': 'YES',
      'GCC_WARN_ABOUT_DEPRECATED_FUNCTIONS': 'YES',
      'GCC_WARN_ABOUT_MISSING_FIELD_INITIALIZERS': 'YES',
      'GCC_WARN_ABOUT_MISSING_NEWLINE': 'YES',
      'GCC_WARN_ABOUT_RETURN_TYPE': 'YES_ERROR',
      'GCC_WARN_CHECK_SWITCH_STATEMENTS': 'YES',
      'GCC_WARN_HIDDEN_VIRTUAL_FUNCTIONS': 'YES',
      'GCC_WARN_MISSING_PARENTHESES': 'YES',
      'GCC_WARN_NON_VIRTUAL_DESTRUCTOR': 'YES',
      'GCC_WARN_SHADOW': 'YES',
      'GCC_WARN_SIGN_COMPARE': 'YES',
      'GCC_WARN_TYPECHECK_CALLS_TO_PRINTF': 'YES',
      'GCC_WARN_UNINITIALIZED_AUTOS': 'YES_AGGRESSIVE',
      'GCC_WARN_UNKNOWN_PRAGMAS': 'YES',
      'GCC_WARN_UNUSED_FUNCTION': 'YES',
      'GCC_WARN_UNUSED_LABEL': 'YES',
      'GCC_WARN_UNUSED_VALUE': 'YES',
      'GCC_WARN_UNUSED_VARIABLE': 'YES',
      # Warnings - Objective-C:
      'CLANG_WARN_DIRECT_OBJC_ISA_USAGE': 'YES_ERROR',
      'CLANG_WARN__DUPLICATE_METHOD_MATCH': 'YES',
      'GCC_WARN_ALLOW_INCOMPLETE_PROTOCOL': 'YES',
      'GCC_WARN_UNDECLARED_SELECTOR': 'YES',
      'CLANG_WARN_OBJC_ROOT_CLASS': 'YES_ERROR',
      # Warning Policies:
      'GCC_TREAT_WARNINGS_AS_ERRORS': 'YES',
      'WARNING_CFLAGS': [
        '-Wall',
      ],
      # Symbols:
      'CLANG_ENABLE_OBJC_ARC': 'YES',
      'GCC_INLINES_ARE_PRIVATE_EXTERN': 'YES', # '-fvisibility-inlines-hidden'
      'GCC_SYMBOLS_PRIVATE_EXTERN': 'YES', # '-fvisibility=hidden'
    },
    'conditions': [
      ['"Direct3D11" in renderers', {
        'sources': [
          '<@(pomdog_library_dxgi_sources)',
          '<@(pomdog_library_direct3d_sources)',
          '<@(pomdog_library_direct3d11_sources)',
        ],
        'link_settings': {
          'libraries': [
            '-ldxgi.lib',
            '-ld3d11.lib',
            '-ld3dcompiler.lib',
            '-ldxguid.lib', # using _IID_ID3D11ShaderReflection
          ],
        },
      }],
      ['"GL4" in renderers', {
        'sources': [
          '<@(pomdog_library_opengl4_sources)',
        ],
      }],
      ['"GL4" in renderers and OS == "win"', {
        'sources': [
          '<@(pomdog_library_win32_opengl_sources)',
        ],
        'defines': [
          'GLEW_STATIC',
        ],
        'dependencies': [
          'dependencies/glew.gyp:glew_static',
        ],
        'include_dirs': [
          '../dependencies/vendor/glew/include',
        ],
        'link_settings': {
          'libraries': [
            '-lopengl32.lib',
          ],
        },
      }],
      ['"Metal" in renderers', {
        'sources': [
          '<@(pomdog_library_metal_sources)',
        ],
      }],
      ['"Metal" in renderers and OS == "mac"', {
        'link_settings': {
          'libraries': [
            '$(SDKROOT)/System/Library/Frameworks/Metal.framework',
          ],
        },
      }],
      ['"Metal" in renderers and OS == "ios"', {
        'link_settings': {
          'libraries': [
            '$(SDKROOT)/System/Library/Frameworks/Metal.framework',
            '$(SDKROOT)/System/Library/Frameworks/MetalKit.framework',
            '$(SDKROOT)/System/Library/Frameworks/ModelIO.framework',
          ],
        },
      }],
      ['"Vulkan" in renderers', {
        'sources': [
          '<@(pomdog_library_vulkan_sources)',
        ],
      }],
      ['audio == "OpenAL"', {
        'sources': [
          '<@(pomdog_library_openal_sources)',
        ],
      }],
      ['audio == "OpenAL" and OS == "mac"', {
        'link_settings': {
          'libraries': [
            '$(SDKROOT)/System/Library/Frameworks/AudioToolBox.framework',
            '$(SDKROOT)/System/Library/Frameworks/OpenAL.framework',
          ],
        },
      }],
      ['audio == "OpenAL" and OS == "ios"', {
        'link_settings': {
          'libraries': [
            '$(SDKROOT)/System/Library/Frameworks/AudioToolBox.framework',
            '$(SDKROOT)/System/Library/Frameworks/OpenAL.framework',
          ],
        },
      }],
      ['audio == "OpenAL" and OS == "linux"', {
        'link_settings': {
          'libraries': [
            '-lopenal',
          ],
        },
      }],
      ['audio == "XAudio2"', {
        'sources': [
          '<@(pomdog_library_xaudio2_sources)',
        ],
        'link_settings': {
          'libraries': [
            '-lxaudio2.lib',
          ],
        },
      }], # audio == "XAudio2"
      ['"DirectInput" in input_devices', {
        'sources': [
          '<@(pomdog_library_directinput_sources)',
        ],
        'link_settings': {
          'libraries': [
            '-ldinput8.lib',
            '-ldxguid.lib',
          ],
        },
      }],
      ['application_platform == "X11"', {
        'sources': [
          '<@(pomdog_library_x11_sources)',
        ],
      }],
      ['application_platform == "X11" and OS == "linux"', {
        'defines': [
          'GLEW_STATIC',
        ],
        'dependencies': [
          'dependencies/glew.gyp:glew_static',
        ],
        'include_dirs': [
          '/usr/X11R6/include',
          '../dependencies/vendor/glew/include',
        ],
        'library_dirs': [
          '/usr/X11R6/lib',
        ],
        'link_settings': {
          'libraries': [
            '-lX11',
            '-lGL',
          ],
        },
      }],
      ['application_platform == "Cocoa"', {
        'sources': [
          '<@(pomdog_library_cocoa_sources)',
        ],
        'link_settings': {
          'libraries': [
            '$(SDKROOT)/System/Library/Frameworks/Cocoa.framework',
            '$(SDKROOT)/System/Library/Frameworks/OpenGL.framework',
            '$(SDKROOT)/System/Library/Frameworks/QuartzCore.framework',
          ],
        },
      }],
      ['OS == "mac" or OS == "ios"', {
        'sources': [
          '<@(pomdog_library_apple_sources)',
        ],
      }],
      ['OS == "mac"', {
        'xcode_settings': {
          'MACOSX_DEPLOYMENT_TARGET': '10.11',
        },
      }],
      ['OS == "ios"', {
        'xcode_settings': {
          'IPHONEOS_DEPLOYMENT_TARGET': '9.0',
          'SDKROOT': 'iphoneos',
        },
        'link_settings': {
          'libraries': [
            '$(SDKROOT)/System/Library/Frameworks/Foundation.framework',
            '$(SDKROOT)/System/Library/Frameworks/UIKit.framework',
          ],
        },
      }],
      ['OS == "win"', {
        'sources': [
          '<@(pomdog_library_win32_sources)',
        ],
        'link_settings': {
          'libraries': [
            '-lkernel32.lib',
            '-luser32.lib',
            '-lgdi32.lib',
            '-lole32.lib',
            '-lwinmm.lib',
            #'-lws2_32.lib',
            #'-lwinspool.lib',
            #'-lcomdlg32.lib',
            #'-ladvapi32.lib',
            '-lshell32.lib',
            #'-loleaut32.lib',
            #'-luuid.lib',
            #'-lodbc32.lib',
            #'-lodbccp32.lib',
          ],
        },
      }], # OS == "win"
      ['OS == "linux"', {
        'sources': [
          '<@(pomdog_library_linux_sources)',
        ],
      }],
    ],
  },
  'targets': [
    {
      'target_name': 'pomdog-static',
      'product_name': 'pomdog',
      'type': 'static_library',
      'xcode_settings': {
        'SKIP_INSTALL': 'YES',
      },
    },
    {
      'target_name': 'pomdog-shared',
      'product_name': 'Pomdog',
      'type': 'shared_library',
      'msvs_guid': 'A8F27BAE-660F-42B4-BC27-D5A435EF94BF',
      'mac_bundle': 1,
      'defines': ['POMDOG_BUILDING_LIBRARY_EXPORTS=1'],
      'xcode_settings': {
        'PRODUCT_NAME': 'Pomdog', #'$(TARGET_NAME)',
        'PRODUCT_BUNDLE_IDENTIFIER': 'net.enginetrouble.pomdog',
        'INFOPLIST_FILE': '../src/Platform.Apple/Info.plist',
        'INSTALL_PATH': '$(LOCAL_LIBRARY_DIR)/Frameworks',
        'SKIP_INSTALL': 'YES',
        #'DEFINES_MODULE': 'YES',
        'DYLIB_INSTALL_NAME_BASE': '@rpath',
        'LD_RUNPATH_SEARCH_PATHS': [
          '$(inherited)',
          '@executable_path/../Frameworks',
          '@loader_path/Frameworks',
        ],
      },
    },
  ],
}
