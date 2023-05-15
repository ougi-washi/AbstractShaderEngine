#include "engine_types.h"
#include "engine_memory.h"

namespace as
{
	// general
	void configure();
	void init_window(const u16& width, const u16& height, const char* title);

	// entities
	std::string variable_enum_to_string(const as::ent::entity_type& in_type);
	as::ent::entity_type variable_string_to_enum(const std::string& in_type_str);
	bool get_model_from_entity(const as::entity& entity, as::model& out_model);
	bool get_model_from_entity(const as::entity* entity, as::model*& out_model);
	bool get_camera_from_entity(const as::entity& entity, as::camera& out_camera);
	bool get_camera_from_entity(const as::entity& entity, as::camera*& out_camera);
	bool get_camera_from_entity(const as::entity* entity, as::camera*& out_camera);
	bool get_world_from_entity(const as::entity& entity, as::world& out_world);
	bool get_world_from_entity(const as::entity* entity, as::world*& out_world);
	bool get_shader_from_entity(const as::entity& entity, as::shader& out_shader);
	bool get_shader_from_entity(const as::entity* entity, as::shader*& out_shader);
	bool get_texture_from_entity(const as::entity& entity, as::texture& out_texture);
	bool get_texture_from_entity(const as::entity* entity, as::texture*& out_texture);
	std::string to_string(const as::entity* entity);
	bool parse_file(const std::string& path, const bool& absolute_path, as::entity*& out_entity);
	bool draw(const std::vector<as::entity*>& entities, const as::world* world);
	size_t get_entity_size(const as::entity* entity);
	void add_sub_entity(as::entity*& parent_entity, as::entity* sub_entity);

	void delete_entity_data(as::entity*& entity);
	void delete_entity_data(void*& data_ptr);

	// transform
	void apply_location(const glm::vec3& location, glm::mat4& transform_matrix);
	void apply_rotation(const glm::vec3& rotation, glm::mat4& transform_matrix);
	void apply_scale(const glm::vec3& scale, glm::mat4& transform_matrix);
	void apply_transform(const as::transform& transform, glm::mat4& transform_matrix);

	// shaders
	//bool create_shader(const char* vert_shader_src, const char* frag_shader_src, as::shader*& out_shader);
	//bool create_shader_from_files(const char* vert_shader_path, const char* frag_shader_path, as::shader*& out_shader);
	//void create_shader_program(u32& out_shader_program);
	//bool bind_shaders_to_program(const u32& shader_program, as::shader*& shader_to_attach);
	//bool deep_copy_shader(const as::shader* source, as::shader*& destination);
	//bool deep_copy_shader(const as::shader* source, void*& destination);
	//size_t get_shader_size(const as::shader& shader);
	//std::string to_string(const as::shader* shader);
	void delete_shader_data(as::shader*& shader);
	void delete_shader_program(const u32& shader_program);
	
	// shader uniforms
	//void add_uniform(const as::uniform& uniform_to_add, as::shader& shader);
	//void set_uniform_bool(const u32& shader_program, const char* name, const bool& value);
	//void set_uniform_integer(const u32& shader_program, const char* name, const i32& value);
	//void set_uniform_f32(const u32& shader_program, const char* name, const f32& value);
	//void set_uniform_vec2(const u32& shader_program, const char* name, const glm::vec2& value);
	//void set_uniform_vec3(const u32& shader_program, const char* name, const glm::vec3& value);
	//void set_uniform_vec4(const u32& shader_program, const char* name, const glm::vec4& value);
	//void set_uniform_mat2(const u32& shader_program, const char* name, const glm::mat2& value);
	//void set_uniform_mat3(const u32& shader_program, const char* name, const glm::mat3& value);
	//void set_uniform_mat4(const u32& shader_program, const char* name, const glm::mat4& value);
	//void bind_uniforms(const as::shader& shader);

	// textures
	//bool load_texture(const char* path, as::texture& out_texture);
	//void add_texture_to_shader(as::texture* texture, as::shader*& shader);
	//bool deep_copy_texture(const as::texture* source, as::texture*& destination);
	//bool deep_copy_texture(const as::texture* source, void*& destination);
	//size_t get_texture_size(const as::texture& texture);
	//size_t get_texture_size(const as::texture* texture);
	//std::string to_string(const as::texture* texture);
	void delete_texture_data(as::texture*& texture);

	// meshes
	//bool create_mesh(const as::vertex* vertices, const size_t& vertices_count, const u32* indices, const size_t& indices_count , as::mesh*& out_mesh);
	//bool assign_shader(as::shader* shader, as::mesh*& out_mesh);
	//bool deep_copy_mesh(const as::mesh* source, as::mesh*& destination);
	//bool deep_copy_mesh(const as::mesh* source, void*& destination);
	//bool draw(const as::mesh* mesh);
	//std::string to_string(const as::mesh* mesh);
	void delete_mesh_data(as::mesh*& mesh);

	// models
	//void load_model(const char* path, as::model*& out_model, std::vector<as::texture>& out_textures);
	//void load_model(const void* model_json_data, as::model*& out_model);
	//void apply_location(const glm::vec3& location, as::model& model);
	//void apply_rotation(const glm::vec3& rotation, as::model& model);
	//void apply_scale(const glm::vec3& scale, as::model& model);
	//void apply_transform(const as::transform& transform, as::model& model);
	//bool draw(const as::model* model, const as::world* world);
	//bool deep_copy_model(const as::model* source, as::model* destination);
	//bool deep_copy_model(const as::model& source, void* destination);
	//size_t get_model_size(const as::model& model);
	//std::string to_string(const as::model* model);
	bool delete_model_data(as::model*& model);

	// render
	void clear_background();
	//bool draw(const std::vector<as::model*>& models, const as::world* world);
	//bool draw(const std::vector<const as::model*>& models, const as::world* world);
	//void update_draw_uniforms(const u32& shader_program, const as::world* world, const glm::mat4& model_transform);

	// camera
	as::camera* find_active_camera(const as::world* world);
	//glm::mat4 get_matrix_view(const as::camera& camera);
	//glm::mat4 get_matrix_projection(const as::camera& camera);
	//void update_camera_vectors(as::camera* camera);
	//size_t get_camera_size(const as::camera& camera);
	std::string to_string(const as::camera* camera);

	// light
	u32 get_all_lights(const as::world* world, as::light**& out_lights);

	// world
	bool draw(const as::world* world, const f32& aspect_ratio);
	//size_t get_world_size(const as::world& world);
	//std::string to_string(const as::world* world);
	void delete_world_data(as::world*& world);
};