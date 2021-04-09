/*
 * Copyright (C) 2021 Patrick Mours. All rights reserved.
 * License: https://github.com/crosire/reshade#license
 */

#include "render_vk.hpp"
#include "render_vk_utils.hpp"

using namespace reshade::api;

const reshade::api::pipeline_state reshade::vulkan::pipeline_states_compute[] = {
	// VkComputePipelineCreateInfo::stage
	reshade::api::pipeline_state::compute_shader,
};
const reshade::api::pipeline_state reshade::vulkan::pipeline_states_graphics[] = {
	// VkGraphicsPipelineCreateInfo::stages
	reshade::api::pipeline_state::vertex_shader,
	reshade::api::pipeline_state::hull_shader,
	reshade::api::pipeline_state::domain_shader,
	reshade::api::pipeline_state::geometry_shader,
	reshade::api::pipeline_state::pixel_shader,
	// VkGraphicsPipelineCreateInfo::pRasterizationState::depthClampEnable
	reshade::api::pipeline_state::depth_clip,
	// VkGraphicsPipelineCreateInfo::pRasterizationState::polygonMode
	reshade::api::pipeline_state::fill_mode,
	// VkGraphicsPipelineCreateInfo::pRasterizationState::cullMode
	reshade::api::pipeline_state::cull_mode,
	// VkGraphicsPipelineCreateInfo::pRasterizationState::frontFace
	reshade::api::pipeline_state::front_face_ccw,
	// VkGraphicsPipelineCreateInfo::pRasterizationState::depthBiasConstantFactor
	reshade::api::pipeline_state::depth_bias,
	// VkGraphicsPipelineCreateInfo::pRasterizationState::depthBiasClamp
	reshade::api::pipeline_state::depth_bias_clamp,
	// VkGraphicsPipelineCreateInfo::pRasterizationState::depthBiasSlopeFactor
	reshade::api::pipeline_state::depth_bias_slope_scaled,
	// VkGraphicsPipelineCreateInfo::pMultisampleState::sampleShadingEnable
	reshade::api::pipeline_state::multisample,
	// VkGraphicsPipelineCreateInfo::pMultisampleState::pSampleMask[0]
	reshade::api::pipeline_state::sample_mask,
	// VkGraphicsPipelineCreateInfo::pMultisampleState::alphaToCoverageEnable
	reshade::api::pipeline_state::sample_alpha_to_coverage,
	// VkGraphicsPipelineCreateInfo::pDepthStencilState::depthTestEnable
	reshade::api::pipeline_state::depth_test,
	// VkGraphicsPipelineCreateInfo::pDepthStencilState::depthWriteEnable
	reshade::api::pipeline_state::depth_write_mask,
	// VkGraphicsPipelineCreateInfo::pDepthStencilState::depthCompareOp
	reshade::api::pipeline_state::depth_func,
	// VkGraphicsPipelineCreateInfo::pDepthStencilState::stencilTestEnable
	reshade::api::pipeline_state::stencil_test,
	// VkGraphicsPipelineCreateInfo::pDepthStencilState::front::failOp
	reshade::api::pipeline_state::stencil_front_fail,
	// VkGraphicsPipelineCreateInfo::pDepthStencilState::front::passOp
	reshade::api::pipeline_state::stencil_front_pass,
	// VkGraphicsPipelineCreateInfo::pDepthStencilState::front::depthFailOp
	reshade::api::pipeline_state::stencil_front_depth_fail,
	// VkGraphicsPipelineCreateInfo::pDepthStencilState::front::compareOp
	reshade::api::pipeline_state::stencil_front_func,
	// VkGraphicsPipelineCreateInfo::pDepthStencilState::front::compareMask
	reshade::api::pipeline_state::stencil_read_mask,
	// VkGraphicsPipelineCreateInfo::pDepthStencilState::front::writeMask
	reshade::api::pipeline_state::stencil_write_mask,
	// VkGraphicsPipelineCreateInfo::pDepthStencilState::front::reference
	reshade::api::pipeline_state::stencil_ref,
	// VkGraphicsPipelineCreateInfo::pDepthStencilState::back::failOp
	reshade::api::pipeline_state::stencil_back_fail,
	// VkGraphicsPipelineCreateInfo::pDepthStencilState::back::passOp
	reshade::api::pipeline_state::stencil_back_pass,
	// VkGraphicsPipelineCreateInfo::pDepthStencilState::back::depthFailOp
	reshade::api::pipeline_state::stencil_back_depth_fail,
	// VkGraphicsPipelineCreateInfo::pDepthStencilState::back::compareOp
	reshade::api::pipeline_state::stencil_back_func,
	// VkGraphicsPipelineCreateInfo::pColorBlendState::pAttachments[0]::blendEnable
	reshade::api::pipeline_state::blend,
	// VkGraphicsPipelineCreateInfo::pColorBlendState::pAttachments[0]::srcColorBlendFactor
	reshade::api::pipeline_state::blend_color_src,
	// VkGraphicsPipelineCreateInfo::pColorBlendState::pAttachments[0]::dstColorBlendFactor
	reshade::api::pipeline_state::blend_color_dest,
	// VkGraphicsPipelineCreateInfo::pColorBlendState::pAttachments[0]::colorBlendOp
	reshade::api::pipeline_state::blend_color_op,
	// VkGraphicsPipelineCreateInfo::pColorBlendState::pAttachments[0]::srcAlphaBlendFactor
	reshade::api::pipeline_state::blend_alpha_src,
	// VkGraphicsPipelineCreateInfo::pColorBlendState::pAttachments[0]::dstAlphaBlendFactor
	reshade::api::pipeline_state::blend_alpha_dest,
	// VkGraphicsPipelineCreateInfo::pColorBlendState::pAttachments[0]::alphaBlendOp
	reshade::api::pipeline_state::blend_alpha_op,
	// VkGraphicsPipelineCreateInfo::pColorBlendState::pAttachments[0]::colorWriteMask
	reshade::api::pipeline_state::render_target_write_mask,
	// VkGraphicsPipelineCreateInfo::pColorBlendState::blendConstants
	reshade::api::pipeline_state::blend_factor,
};

void reshade::vulkan::fill_pipeline_state_values(const VkComputePipelineCreateInfo &create_info, uint32_t values[])
{
	values[0] = 0; // TODO: CS
}
void reshade::vulkan::fill_pipeline_state_values(const VkGraphicsPipelineCreateInfo &create_info, uint32_t values[])
{
	values[0] = 0; // TODO: VS
	values[1] = 0; // TODO: HS
	values[2] = 0; // TODO: DS
	values[3] = 0; // TODO: GS
	values[4] = 0; // TODO: PS

	if (create_info.pRasterizationState != nullptr)
	{
		const VkPipelineRasterizationStateCreateInfo &info = *create_info.pRasterizationState;
		values[5] = info.depthClampEnable;
		values[6] = info.polygonMode;
		values[7] = info.cullMode;
		values[8] = info.frontFace;
		values[9] = static_cast<uint32_t>(static_cast<int32_t>(info.depthBiasConstantFactor));
		values[10] = *reinterpret_cast<const uint32_t *>(&info.depthBiasClamp);
		values[11] = *reinterpret_cast<const uint32_t *>(&info.depthBiasSlopeFactor);
	}
	else
	{
		assert(false);
	}

	if (create_info.pMultisampleState != nullptr)
	{
		const VkPipelineMultisampleStateCreateInfo &info = *create_info.pMultisampleState;
		values[12] = info.sampleShadingEnable;
		values[13] = info.pSampleMask[0];
		values[14] = info.alphaToCoverageEnable;
	}
	else
	{
		values[12] = values[13] = values[14] = 0;
	}

	if (create_info.pDepthStencilState != nullptr)
	{
		const VkPipelineDepthStencilStateCreateInfo &info = *create_info.pDepthStencilState;
		values[15] = info.depthTestEnable;
		values[16] = info.depthWriteEnable;
		values[17] = info.depthCompareOp;
		values[18] = info.stencilTestEnable;
		values[19] = info.front.failOp;
		values[20] = info.front.passOp;
		values[21] = info.front.depthFailOp;
		values[22] = info.front.compareOp;
		values[23] = info.front.compareMask;
		values[24] = info.front.writeMask;
		values[25] = info.front.reference;
		values[26] = info.back.failOp;
		values[27] = info.back.passOp;
		values[28] = info.back.depthFailOp;
		values[29] = info.back.compareOp;
	}
	else
	{
		values[15] = VK_FALSE;
		values[16] = 0;
		values[17] = 0;
		values[18] = VK_FALSE;
		values[19] = values[20] = values[21] = VK_STENCIL_OP_KEEP;
		values[22] = VK_COMPARE_OP_ALWAYS;
		values[23] = 0xFFFFFFFF;
		values[24] = 0xFFFFFFFF;
		values[25] = 0xFFFFFFFF;
		values[26] = values[27] = values[28] = VK_STENCIL_OP_KEEP;
		values[29] = VK_COMPARE_OP_ALWAYS;
	}

	if (create_info.pColorBlendState != nullptr &&
		create_info.pColorBlendState->pAttachments != nullptr)
	{
		const VkPipelineColorBlendStateCreateInfo &info = *create_info.pColorBlendState;
		values[30] = info.pAttachments[0].blendEnable;
		values[31] = info.pAttachments[0].srcColorBlendFactor;
		values[32] = info.pAttachments[0].dstColorBlendFactor;
		values[33] = info.pAttachments[0].colorBlendOp;
		values[34] = info.pAttachments[0].srcAlphaBlendFactor;
		values[35] = info.pAttachments[0].dstAlphaBlendFactor;
		values[36] = info.pAttachments[0].alphaBlendOp;
		values[37] = info.pAttachments[0].colorWriteMask;
		values[38] =
			((static_cast<uint32_t>(info.blendConstants[0] * 255.f) & 0xFF)) |
			((static_cast<uint32_t>(info.blendConstants[1] * 255.f) & 0xFF) << 8) |
			((static_cast<uint32_t>(info.blendConstants[2] * 255.f) & 0xFF) << 16) |
			((static_cast<uint32_t>(info.blendConstants[3] * 255.f) & 0xFF) << 24);
	}
	else
	{
		values[30] = VK_FALSE;
		values[31] = VK_BLEND_FACTOR_ONE;
		values[32] = VK_BLEND_FACTOR_ZERO;
		values[33] = VK_BLEND_OP_ADD;
		values[34] = VK_BLEND_FACTOR_ONE;
		values[35] = VK_BLEND_FACTOR_ZERO;
		values[36] = VK_BLEND_OP_ADD;
		values[37] = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		values[38] = 0xFFFFFFFF;
	}
}

auto reshade::vulkan::convert_usage_to_access(resource_usage state) -> VkAccessFlags
{
	VkAccessFlags result = 0;
	if ((state & resource_usage::depth_stencil_read) != 0)
		result |= VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
	if ((state & resource_usage::depth_stencil_write) != 0)
		result |= VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
	if ((state & resource_usage::render_target) != 0)
		result |= VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	if ((state & resource_usage::shader_resource) != 0)
		result |= VK_ACCESS_SHADER_READ_BIT;
	if ((state & resource_usage::unordered_access) != 0)
		result |= VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT;
	if ((state & (resource_usage::copy_dest | resource_usage::resolve_dest)) != 0)
		result |= VK_ACCESS_TRANSFER_WRITE_BIT;
	if ((state & (resource_usage::copy_source | resource_usage::resolve_source)) != 0)
		result |= VK_ACCESS_TRANSFER_READ_BIT;
	if ((state & resource_usage::index_buffer) != 0)
		result |= VK_ACCESS_INDEX_READ_BIT;
	if ((state & resource_usage::vertex_buffer) != 0)
		result |= VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT;
	if ((state & resource_usage::constant_buffer) != 0)
		result |= VK_ACCESS_UNIFORM_READ_BIT;
	return result;
}
auto reshade::vulkan::convert_usage_to_image_layout(resource_usage state) -> VkImageLayout
{
	switch (state)
	{
	case resource_usage::undefined:
		return VK_IMAGE_LAYOUT_UNDEFINED;
	case resource_usage::depth_stencil:
	case resource_usage::depth_stencil_read:
	case resource_usage::depth_stencil_write:
		return VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
	case resource_usage::render_target:
		return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
	case resource_usage::shader_resource:
	case resource_usage::shader_resource_pixel:
	case resource_usage::shader_resource_non_pixel:
		return VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	default: // Default to general layout if multiple usage flags are specified
	case resource_usage::unordered_access:
		return VK_IMAGE_LAYOUT_GENERAL;
	case resource_usage::copy_dest:
	case resource_usage::resolve_dest:
		return VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
	case resource_usage::copy_source:
	case resource_usage::resolve_source:
		return VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
	}
}
auto reshade::vulkan::convert_usage_to_pipeline_stage(resource_usage state) -> VkPipelineStageFlags
{
	if (state == resource_usage::undefined)
		return VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT; // Do not wait on any previous stage

	VkPipelineStageFlags result = 0;
	if ((state & resource_usage::depth_stencil_read) != 0)
		result |= VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
	if ((state & resource_usage::depth_stencil_write) != 0)
		result |= VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
	if ((state & resource_usage::render_target) != 0)
		result |= VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	if ((state & (resource_usage::shader_resource_pixel | resource_usage::constant_buffer)) != 0)
		result |= VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
	if ((state & (resource_usage::shader_resource_non_pixel | resource_usage::constant_buffer)) != 0)
		result |= VK_PIPELINE_STAGE_VERTEX_SHADER_BIT | VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT | VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT | VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
	if ((state & resource_usage::unordered_access) != 0)
		result |= VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
	if ((state & (resource_usage::copy_dest | resource_usage::copy_source | resource_usage::resolve_dest | resource_usage::resolve_source)) != 0)
		result |= VK_PIPELINE_STAGE_TRANSFER_BIT;
	if ((state & (resource_usage::index_buffer | resource_usage::vertex_buffer)) != 0)
		result |= VK_PIPELINE_STAGE_VERTEX_INPUT_BIT;
	return result;
}

void reshade::vulkan::convert_usage_to_image_usage_flags(resource_usage usage, VkImageUsageFlags &image_flags)
{
	if ((usage & resource_usage::render_target) != 0)
		image_flags |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	else
		image_flags &= ~VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	if ((usage & resource_usage::depth_stencil) != 0)
		image_flags |= VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
	else
		image_flags &= ~VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;

	if ((usage & resource_usage::shader_resource) != 0)
		image_flags |= VK_IMAGE_USAGE_SAMPLED_BIT;
	else
		image_flags &= ~VK_IMAGE_USAGE_SAMPLED_BIT;

	if ((usage & resource_usage::unordered_access) != 0)
		image_flags |= VK_IMAGE_USAGE_STORAGE_BIT;
	else
		image_flags &= ~VK_IMAGE_USAGE_STORAGE_BIT;

	if ((usage & (resource_usage::copy_dest | resource_usage::resolve_dest)) != 0)
		image_flags |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
	else
		image_flags &= ~VK_IMAGE_USAGE_TRANSFER_DST_BIT;

	if ((usage & (resource_usage::copy_source | resource_usage::resolve_source)) != 0)
		image_flags |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
	else
		image_flags &= ~VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
}
static inline void convert_image_usage_flags_to_usage(const VkImageUsageFlags image_flags, resource_usage &usage)
{
	if ((image_flags & VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT) != 0)
		usage |= resource_usage::render_target;
	if ((image_flags & VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT) != 0)
		usage |= resource_usage::depth_stencil;
	if ((image_flags & VK_IMAGE_USAGE_SAMPLED_BIT) != 0)
		usage |= resource_usage::shader_resource;
	if ((image_flags & VK_IMAGE_USAGE_STORAGE_BIT) != 0)
		usage |= resource_usage::unordered_access;
	if ((image_flags & VK_IMAGE_USAGE_TRANSFER_DST_BIT) != 0)
		usage |= resource_usage::copy_dest;
	if ((image_flags & VK_IMAGE_USAGE_TRANSFER_SRC_BIT) != 0)
		usage |= resource_usage::copy_source;
}
void reshade::vulkan::convert_usage_to_buffer_usage_flags(resource_usage usage, VkBufferUsageFlags &buffer_flags)
{
	if ((usage & resource_usage::index_buffer) != 0)
		buffer_flags |= VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
	else
		buffer_flags &= ~VK_BUFFER_USAGE_INDEX_BUFFER_BIT;

	if ((usage & resource_usage::vertex_buffer) != 0)
		buffer_flags |= VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	else
		buffer_flags &= ~VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;

	if ((usage & resource_usage::constant_buffer) != 0)
		buffer_flags |= VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
	else
		buffer_flags &= ~VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;

	if ((usage & resource_usage::unordered_access) != 0)
		buffer_flags |= VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
	else
		buffer_flags &= ~VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;

	if ((usage & resource_usage::copy_dest) != 0)
		buffer_flags |= VK_BUFFER_USAGE_TRANSFER_DST_BIT;
	else
		buffer_flags &= ~VK_BUFFER_USAGE_TRANSFER_DST_BIT;

	if ((usage & resource_usage::copy_source) != 0)
		buffer_flags |= VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
	else
		buffer_flags &= ~VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
}
static inline void convert_buffer_usage_flags_to_usage(const VkBufferUsageFlags buffer_flags, resource_usage &usage)
{
	if ((buffer_flags & VK_BUFFER_USAGE_INDEX_BUFFER_BIT) != 0)
		usage |= resource_usage::index_buffer;
	if ((buffer_flags & VK_BUFFER_USAGE_VERTEX_BUFFER_BIT) != 0)
		usage |= resource_usage::vertex_buffer;
	if ((buffer_flags & VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT) != 0)
		usage |= resource_usage::constant_buffer;
	if ((buffer_flags & VK_BUFFER_USAGE_STORAGE_BUFFER_BIT) != 0)
		usage |= resource_usage::unordered_access;
	if ((buffer_flags & VK_BUFFER_USAGE_TRANSFER_DST_BIT) != 0)
		usage |= resource_usage::copy_dest;
	if ((buffer_flags & VK_BUFFER_USAGE_TRANSFER_SRC_BIT) != 0)
		usage |= resource_usage::copy_source;
}

void reshade::vulkan::convert_resource_desc(const resource_desc &desc, VkImageCreateInfo &create_info)
{
	switch (desc.type)
	{
	default:
		assert(false);
		break;
	case resource_type::texture_1d:
		create_info.imageType = VK_IMAGE_TYPE_1D;
		create_info.extent = { desc.width, 1u, 1u };
		create_info.arrayLayers = desc.depth_or_layers;
		break;
	case resource_type::texture_2d:
		create_info.imageType = VK_IMAGE_TYPE_2D;
		create_info.extent = { desc.width, desc.height, 1u };
		create_info.arrayLayers = desc.depth_or_layers;
		break;
	case resource_type::texture_3d:
		create_info.imageType = VK_IMAGE_TYPE_3D;
		create_info.extent = { desc.width, desc.height, desc.depth_or_layers };
		create_info.arrayLayers = 1u;
		break;
	}

	create_info.format = static_cast<VkFormat>(desc.format);
	create_info.mipLevels = desc.levels;
	create_info.samples = static_cast<VkSampleCountFlagBits>(desc.samples);
	convert_usage_to_image_usage_flags(desc.usage, create_info.usage);
}
void reshade::vulkan::convert_resource_desc(const resource_desc &desc, VkBufferCreateInfo &create_info)
{
	assert(desc.type == resource_type::buffer);
	create_info.size = desc.size;
	convert_usage_to_buffer_usage_flags(desc.usage, create_info.usage);
}
resource_desc reshade::vulkan::convert_resource_desc(const VkImageCreateInfo &create_info)
{
	resource_desc desc = {};
	switch (create_info.imageType)
	{
	default:
		assert(false);
		desc.type = resource_type::unknown;
		break;
	case VK_IMAGE_TYPE_1D:
		desc.type = resource_type::texture_1d;
		desc.width = create_info.extent.width;
		assert(create_info.extent.height == 1 && create_info.extent.depth == 1);
		desc.height = 1;
		assert(create_info.arrayLayers <= std::numeric_limits<uint16_t>::max());
		desc.depth_or_layers = static_cast<uint16_t>(create_info.arrayLayers);
		break;
	case VK_IMAGE_TYPE_2D:
		desc.type = resource_type::texture_2d;
		desc.width = create_info.extent.width;
		desc.height = create_info.extent.height;
		assert(create_info.extent.depth == 1);
		assert(create_info.arrayLayers <= std::numeric_limits<uint16_t>::max());
		desc.depth_or_layers = static_cast<uint16_t>(create_info.arrayLayers);
		break;
	case VK_IMAGE_TYPE_3D:
		desc.type = resource_type::texture_3d;
		desc.width = create_info.extent.width;
		desc.height = create_info.extent.height;
		assert(create_info.extent.depth <= std::numeric_limits<uint16_t>::max());
		desc.depth_or_layers = static_cast<uint16_t>(create_info.extent.depth);
		assert(create_info.arrayLayers == 1);
		break;
	}

	assert(create_info.mipLevels <= std::numeric_limits<uint16_t>::max());
	desc.levels = static_cast<uint16_t>(create_info.mipLevels);
	desc.format = static_cast<uint32_t>(create_info.format);
	desc.samples = static_cast<uint16_t>(create_info.samples);

	convert_image_usage_flags_to_usage(create_info.usage, desc.usage);
	if (desc.type == resource_type::texture_2d && (
		create_info.usage & (desc.samples > 1 ? VK_IMAGE_USAGE_TRANSFER_SRC_BIT : VK_IMAGE_USAGE_TRANSFER_DST_BIT)) != 0)
		desc.usage |= desc.samples > 1 ? resource_usage::resolve_source : resource_usage::resolve_dest;

	return desc;
}
resource_desc reshade::vulkan::convert_resource_desc(const VkBufferCreateInfo &create_info)
{
	resource_desc desc = {};
	desc.type = resource_type::buffer;
	desc.size = create_info.size;
	convert_buffer_usage_flags_to_usage(create_info.usage, desc.usage);
	return desc;
}

void reshade::vulkan::convert_resource_view_desc(const resource_view_desc &desc, VkImageViewCreateInfo &create_info)
{
	switch (desc.type)
	{
	default:
		assert(false);
		break;
	case resource_view_type::texture_1d:
		create_info.viewType = VK_IMAGE_VIEW_TYPE_1D;
		break;
	case resource_view_type::texture_1d_array:
		create_info.viewType = VK_IMAGE_VIEW_TYPE_1D_ARRAY;
		break;
	case resource_view_type::texture_2d:
		create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
		break;
	case resource_view_type::texture_2d_array:
		create_info.viewType = VK_IMAGE_VIEW_TYPE_2D_ARRAY;
		break;
	case resource_view_type::texture_3d:
		create_info.viewType = VK_IMAGE_VIEW_TYPE_3D;
		break;
	case resource_view_type::texture_cube:
		create_info.viewType = VK_IMAGE_VIEW_TYPE_CUBE;
		break;
	case resource_view_type::texture_cube_array:
		create_info.viewType = VK_IMAGE_VIEW_TYPE_CUBE_ARRAY;
		break;
	}

	create_info.format = static_cast<VkFormat>(desc.format);
	create_info.subresourceRange.baseMipLevel = desc.first_level;
	create_info.subresourceRange.levelCount = desc.levels;
	create_info.subresourceRange.baseArrayLayer = desc.first_layer;
	create_info.subresourceRange.layerCount = desc.layers;
}
void reshade::vulkan::convert_resource_view_desc(const resource_view_desc &desc, VkBufferViewCreateInfo &create_info)
{
	assert(desc.type == resource_view_type::buffer);

	create_info.format = static_cast<VkFormat>(desc.format);
	create_info.offset = desc.offset;
	create_info.range = desc.size;
}
resource_view_desc reshade::vulkan::convert_resource_view_desc(const VkImageViewCreateInfo &create_info)
{
	resource_view_desc desc = {};
	switch (create_info.viewType)
	{
	default:
		assert(false);
		desc.type = resource_view_type::unknown;
		break;
	case VK_IMAGE_VIEW_TYPE_1D:
		desc.type = resource_view_type::texture_1d;
		break;
	case VK_IMAGE_VIEW_TYPE_1D_ARRAY:
		desc.type = resource_view_type::texture_1d_array;
		break;
	case VK_IMAGE_VIEW_TYPE_2D:
		desc.type = resource_view_type::texture_2d;
		break;
	case VK_IMAGE_VIEW_TYPE_2D_ARRAY:
		desc.type = resource_view_type::texture_2d_array;
		break;
	case VK_IMAGE_VIEW_TYPE_3D:
		desc.type = resource_view_type::texture_3d;
		break;
	case VK_IMAGE_VIEW_TYPE_CUBE:
		desc.type = resource_view_type::texture_cube;
		break;
	case VK_IMAGE_VIEW_TYPE_CUBE_ARRAY:
		desc.type = resource_view_type::texture_cube_array;
		break;
	}

	desc.format = static_cast<uint32_t>(create_info.format);
	desc.first_level = create_info.subresourceRange.baseMipLevel;
	desc.levels = create_info.subresourceRange.levelCount;
	desc.first_layer = create_info.subresourceRange.baseArrayLayer;
	desc.layers = create_info.subresourceRange.layerCount;

	return desc;
}
resource_view_desc reshade::vulkan::convert_resource_view_desc(const VkBufferViewCreateInfo &create_info)
{
	resource_view_desc desc = {};
	desc.type = resource_view_type::buffer;
	desc.format = static_cast<uint32_t>(create_info.format);
	desc.offset = create_info.offset;
	desc.size = create_info.sType;

	return desc;
}
