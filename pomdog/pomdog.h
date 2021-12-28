// Copyright mogemimi. Distributed under the MIT license.

#pragma once

/// Root namespace for the Pomdog game engine.
namespace pomdog {
} // namespace pomdog

#include "pomdog/application/game.h"
#include "pomdog/application/game_host.h"
#include "pomdog/application/game_window.h"
#include "pomdog/application/mouse_cursor.h"

#include "pomdog/chrono/duration.h"
#include "pomdog/chrono/game_clock.h"
#include "pomdog/chrono/time_point.h"
#include "pomdog/chrono/timer.h"

#include "pomdog/audio/audio_channels.h"
#include "pomdog/audio/audio_clip.h"
#include "pomdog/audio/audio_emitter.h"
#include "pomdog/audio/audio_engine.h"
#include "pomdog/audio/audio_listener.h"
#include "pomdog/audio/sound_effect.h"
#include "pomdog/audio/sound_state.h"

#include "pomdog/content/asset_builders/pipeline_state_builder.h"
#include "pomdog/content/asset_builders/shader_builder.h"
#include "pomdog/content/asset_manager.h"

#include "pomdog/filesystem/file_system.h"

#include "pomdog/math/bounding_box.h"
#include "pomdog/math/bounding_box2d.h"
#include "pomdog/math/bounding_circle.h"
#include "pomdog/math/bounding_frustum.h"
#include "pomdog/math/bounding_sphere.h"
#include "pomdog/math/color.h"
#include "pomdog/math/containment_type.h"
#include "pomdog/math/degree.h"
#include "pomdog/math/math.h"
#include "pomdog/math/matrix2x2.h"
#include "pomdog/math/matrix3x2.h"
#include "pomdog/math/matrix3x3.h"
#include "pomdog/math/matrix4x4.h"
#include "pomdog/math/plane.h"
#include "pomdog/math/plane_intersection_type.h"
#include "pomdog/math/point2d.h"
#include "pomdog/math/point3d.h"
#include "pomdog/math/quaternion.h"
#include "pomdog/math/radian.h"
#include "pomdog/math/ray.h"
#include "pomdog/math/rectangle.h"
#include "pomdog/math/vector2.h"
#include "pomdog/math/vector3.h"
#include "pomdog/math/vector4.h"

#include "pomdog/network/array_view.h"
#include "pomdog/network/http_client.h"
#include "pomdog/network/http_method.h"
#include "pomdog/network/http_request.h"
#include "pomdog/network/http_response.h"
#include "pomdog/network/io_service.h"
#include "pomdog/network/tcp_stream.h"
#include "pomdog/network/tls_stream.h"
#include "pomdog/network/udp_stream.h"

#include "pomdog/logging/log.h"
#include "pomdog/logging/log_channel.h"
#include "pomdog/logging/log_entry.h"
#include "pomdog/logging/log_level.h"

#include "pomdog/gpu/blend_description.h"
#include "pomdog/gpu/blend_factor.h"
#include "pomdog/gpu/blend_operation.h"
#include "pomdog/gpu/buffer_usage.h"
#include "pomdog/gpu/comparison_function.h"
#include "pomdog/gpu/constant_buffer.h"
#include "pomdog/gpu/cull_mode.h"
#include "pomdog/gpu/depth_stencil_buffer.h"
#include "pomdog/gpu/depth_stencil_description.h"
#include "pomdog/gpu/depth_stencil_operation.h"
#include "pomdog/gpu/effect_annotation.h"
#include "pomdog/gpu/effect_constant_description.h"
#include "pomdog/gpu/effect_reflection.h"
#include "pomdog/gpu/effect_variable.h"
#include "pomdog/gpu/effect_variable_class.h"
#include "pomdog/gpu/effect_variable_type.h"
#include "pomdog/gpu/fill_mode.h"
#include "pomdog/gpu/graphics_command_list.h"
#include "pomdog/gpu/graphics_command_queue.h"
#include "pomdog/gpu/graphics_device.h"
#include "pomdog/gpu/index_buffer.h"
#include "pomdog/gpu/index_element_size.h"
#include "pomdog/gpu/input_classification.h"
#include "pomdog/gpu/input_element.h"
#include "pomdog/gpu/input_element_format.h"
#include "pomdog/gpu/input_layout_description.h"
#include "pomdog/gpu/input_layout_helper.h"
#include "pomdog/gpu/pipeline_state.h"
#include "pomdog/gpu/pipeline_state_description.h"
#include "pomdog/gpu/presentation_parameters.h"
#include "pomdog/gpu/primitive_topology.h"
#include "pomdog/gpu/rasterizer_description.h"
#include "pomdog/gpu/render_pass.h"
#include "pomdog/gpu/render_target2d.h"
#include "pomdog/gpu/render_target_blend_description.h"
#include "pomdog/gpu/sampler_description.h"
#include "pomdog/gpu/sampler_state.h"
#include "pomdog/gpu/shader.h"
#include "pomdog/gpu/shader_language.h"
#include "pomdog/gpu/shader_pipeline_stage.h"
#include "pomdog/gpu/stencil_operation.h"
#include "pomdog/gpu/surface_format.h"
#include "pomdog/gpu/texture.h"
#include "pomdog/gpu/texture2d.h"
#include "pomdog/gpu/texture_address_mode.h"
#include "pomdog/gpu/texture_filter.h"
#include "pomdog/gpu/vertex_buffer.h"
#include "pomdog/gpu/viewport.h"

#include "pomdog/input/button_state.h"
#include "pomdog/input/gamepad.h"
#include "pomdog/input/gamepad_buttons.h"
#include "pomdog/input/gamepad_capabilities.h"
#include "pomdog/input/gamepad_dpad.h"
#include "pomdog/input/gamepad_state.h"
#include "pomdog/input/gamepad_thumbsticks.h"
#include "pomdog/input/gamepad_uuid.h"
#include "pomdog/input/key_state.h"
#include "pomdog/input/keyboard.h"
#include "pomdog/input/keyboard_state.h"
#include "pomdog/input/keys.h"
#include "pomdog/input/mouse.h"
#include "pomdog/input/mouse_buttons.h"
#include "pomdog/input/mouse_state.h"
#include "pomdog/input/player_index.h"
#include "pomdog/input/touch_location.h"
#include "pomdog/input/touch_location_state.h"

#include "pomdog/signals/connection.h"
#include "pomdog/signals/connection_list.h"
#include "pomdog/signals/delegate.h"
#include "pomdog/signals/event_queue.h"
#include "pomdog/signals/scoped_connection.h"
#include "pomdog/signals/signal.h"
#include "pomdog/signals/signal_helpers.h"

#include "pomdog/utility/assert.h"
#include "pomdog/utility/errors.h"
#include "pomdog/utility/path_helper.h"
#include "pomdog/utility/string_helper.h"

#include "pomdog/basic/export.h"
#include "pomdog/basic/platform.h"
#include "pomdog/basic/version.h"
