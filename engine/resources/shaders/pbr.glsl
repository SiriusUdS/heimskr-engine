#version 330 core
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_uvs;

// The model matrix encapsulates the model's position, rotation, and scale in the world.
// It's represented as Model = Translation * Rotation * Scale
// It receives a local space coordinate and transforms it into world space.
uniform mat4 u_model;
// The view matrix represents the camera's position and orientation in the world.
// It's represented as View = LookAt(camera_position, target_position, up_vector)
// It transforms world space coordinates into view space coordinates.
uniform mat4 u_view;
// The projection matrix deals with the camera's field of view, aspect ratio, and near/far clipping planes to transform a 3D point into a 2D screen space.
// It's represented as Projection = Perspective(fov, aspect_ratio, near_plane, far_plane)
// It transforms view space coordinates into clip space (Screen space) coordinates.
uniform mat4 u_projection;

void main() {
	gl_Position = u_projection * u_view * u_model * vec4(in_position, 1.0);
}

++VERTEX++

#version 330 core
layout (location = 0) out vec4 out_fragment;

void main() {
	// Outputs a contant color
	out_fragment = vec4(0.6, 0.5, 0.7, 1.0);
}

++FRAGMENT++