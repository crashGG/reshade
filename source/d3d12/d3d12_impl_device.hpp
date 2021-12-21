/*
 * Copyright (C) 2021 Patrick Mours. All rights reserved.
 * License: https://github.com/crosire/reshade#license
 */

#pragma once

#include "addon_manager.hpp"
#include "descriptor_heap.hpp"
#include <dxgi1_5.h>
#include <shared_mutex>

struct D3D12DescriptorHeap;

namespace reshade::d3d12
{
	class device_impl : public api::api_object_impl<ID3D12Device *, api::device>
	{
		friend class command_list_impl;
		friend class command_queue_impl;

	public:
		explicit device_impl(ID3D12Device *device);
		~device_impl();

		api::device_api get_api() const final { return api::device_api::d3d12; }

		bool check_capability(api::device_caps capability) const final;
		bool check_format_support(api::format format, api::resource_usage usage) const final;

		bool create_sampler(const api::sampler_desc &desc, api::sampler *out_handle) final;
		void destroy_sampler(api::sampler handle) final;

		bool create_resource(const api::resource_desc &desc, const api::subresource_data *initial_data, api::resource_usage initial_state, api::resource *out_handle, HANDLE *shared_handle = nullptr) final;
		void destroy_resource(api::resource handle) final;

		api::resource_desc get_resource_desc(api::resource resource) const final;

		bool create_resource_view(api::resource resource, api::resource_usage usage_type, const api::resource_view_desc &desc, api::resource_view *out_handle) final;
		void destroy_resource_view(api::resource_view handle) final;

		api::resource get_resource_from_view(api::resource_view view) const final;
		api::resource_view_desc get_resource_view_desc(api::resource_view view) const final;

		bool map_buffer_region(api::resource resource, uint64_t offset, uint64_t size, api::map_access access, void **out_data) final;
		void unmap_buffer_region(api::resource resource) final;
		bool map_texture_region(api::resource resource, uint32_t subresource, const api::subresource_box *box, api::map_access access, api::subresource_data *out_data) final;
		void unmap_texture_region(api::resource resource, uint32_t subresource) final;

		void update_buffer_region(const void *data, api::resource resource, uint64_t offset, uint64_t size) final;
		void update_texture_region(const api::subresource_data &data, api::resource resource, uint32_t subresource, const api::subresource_box *box) final;

		bool create_pipeline(const api::pipeline_desc &desc, uint32_t dynamic_state_count, const api::dynamic_state *dynamic_states, api::pipeline *out_handle) final;
		bool create_compute_pipeline(const api::pipeline_desc &desc, api::pipeline *out_handle);
		bool create_graphics_pipeline(const api::pipeline_desc &desc, api::pipeline *out_handle);
		void destroy_pipeline(api::pipeline handle) final;

		bool create_pipeline_layout(uint32_t param_count, const api::pipeline_layout_param *params, api::pipeline_layout *out_handle) final;
		void destroy_pipeline_layout(api::pipeline_layout handle) final;

		bool allocate_descriptor_sets(uint32_t count, api::pipeline_layout layout, uint32_t layout_param, api::descriptor_set *out_sets) final;
		void free_descriptor_sets(uint32_t count, const api::descriptor_set *sets) final;

		void get_descriptor_pool_offset(api::descriptor_set set, uint32_t binding, uint32_t array_offset, api::descriptor_pool *out_pool, uint32_t *out_offset) const final;

		void copy_descriptor_sets(uint32_t count, const api::descriptor_set_copy *copies) final;
		void update_descriptor_sets(uint32_t count, const api::descriptor_set_update *updates) final;

		bool create_query_pool(api::query_type type, uint32_t size, api::query_pool *out_handle) final;
		void destroy_query_pool(api::query_pool handle) final;

		bool get_query_pool_results(api::query_pool pool, uint32_t first, uint32_t count, void *results, uint32_t stride) final;

		void set_resource_name(api::resource handle, const char *name) final;
		void set_resource_view_name(api::resource_view, const char * ) final {}

		bool resolve_gpu_address(D3D12_GPU_VIRTUAL_ADDRESS address, api::resource *out_resource, uint64_t *out_offset) const;

		D3D12_CPU_DESCRIPTOR_HANDLE convert_to_original_cpu_descriptor_handle(api::descriptor_set set, D3D12_DESCRIPTOR_HEAP_TYPE &type) const;
		D3D12_GPU_DESCRIPTOR_HANDLE convert_to_original_gpu_descriptor_handle(api::descriptor_set set) const;
		D3D12_CPU_DESCRIPTOR_HANDLE convert_to_original_cpu_descriptor_handle(D3D12_CPU_DESCRIPTOR_HANDLE handle, D3D12_DESCRIPTOR_HEAP_TYPE type) const;
		D3D12_GPU_DESCRIPTOR_HANDLE convert_to_original_gpu_descriptor_handle(D3D12_GPU_DESCRIPTOR_HANDLE handle) const;

		__forceinline D3D12_CPU_DESCRIPTOR_HANDLE offset_descriptor_handle(D3D12_CPU_DESCRIPTOR_HANDLE handle, SIZE_T offset, D3D12_DESCRIPTOR_HEAP_TYPE type) const
		{
			handle.ptr += offset * _descriptor_handle_size[type];
			return handle;
		}
		__forceinline D3D12_GPU_DESCRIPTOR_HANDLE offset_descriptor_handle(D3D12_GPU_DESCRIPTOR_HANDLE handle, SIZE_T offset, D3D12_DESCRIPTOR_HEAP_TYPE type) const
		{
			handle.ptr += offset * _descriptor_handle_size[type];
			return handle;
		}

	protected:
		void register_resource(ID3D12Resource *resource);
		void unregister_resource(ID3D12Resource *resource);

		void register_descriptor_heap(D3D12DescriptorHeap *heap);

		inline void register_resource_view(D3D12_CPU_DESCRIPTOR_HANDLE handle, ID3D12Resource *resource, const api::resource_view_desc &desc)
		{
			const std::unique_lock<std::shared_mutex> lock(_device_mutex);
			_views.insert_or_assign(handle.ptr, std::make_pair(resource, desc));
		}

	private:
		std::vector<command_queue_impl *> _queues;

		UINT _descriptor_handle_size[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES];

		descriptor_heap_cpu _view_heaps[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES];
		descriptor_heap_gpu<D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER, 128, 128> _gpu_sampler_heap;
		descriptor_heap_gpu<D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 1024, 2048> _gpu_view_heap;

		mutable std::shared_mutex _device_mutex;
#if RESHADE_ADDON
		std::vector<D3D12DescriptorHeap *> _descriptor_heaps;
		std::vector<std::pair<ID3D12Resource *, D3D12_GPU_VIRTUAL_ADDRESS_RANGE>> _buffer_gpu_addresses;
#endif
		std::unordered_map<SIZE_T, std::pair<ID3D12Resource *, api::resource_view_desc>> _views;

		com_ptr<ID3D12PipelineState> _mipmap_pipeline;
		com_ptr<ID3D12RootSignature> _mipmap_signature;
	};
}
