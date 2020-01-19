/**
 * Copyright (C) 2015 by Liangliang Nan (liangliang.nan@gmail.com)
 * https://3d.bk.tudelft.nl/liangliang/
 *
 * This file is part of Easy3D. If it is useful in your research/work,
 * I would be grateful if you show your appreciation by citing it:
 * ------------------------------------------------------------------
 *      Liangliang Nan.
 *      Easy3D: a lightweight, easy-to-use, and efficient C++
 *      library for processing and rendering 3D data. 2018.
 * ------------------------------------------------------------------
 * Easy3D is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License Version 3
 * as published by the Free Software Foundation.
 *
 * Easy3D is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EASY3D_TRANSFORM_H
#define EASY3D_TRANSFORM_H


#include <easy3d/core/types.h>


// Defines functions that generate common transformation matrices.
// NOTE: using right handed coordinate system.
//
// The matrices generated by this extension use standard OpenGL fixed-function
// conventions. For example, the lookAt function generates a transform from world
// space into the specific eye space that the projective matrix functions 
// (perspective, ortho, etc.) are designed to expect. The OpenGL compatibility
// specifications defines the particular layout of this eye space.

namespace easy3d {

    namespace transform {

        // Creates a matrix for an orthographic parallel viewing volume. Simulating glFrustum()
        // near: Specifies the distance from the viewer to the near clipping plane (always positive).
        // far:  Specifies the distance from the viewer to the far clipping plane (always positive).
        // see http://www.songho.ca/opengl/gl_projectionmatrix.html
        //     https://ksimek.github.io/2013/06/03/calibrated_cameras_in_opengl/
        mat4 ortho(float left, float right, float bottom, float top, float near, float far);

        // Creates a matrix for projecting two-dimensional coordinates onto the screen.
        mat4 ortho(float left, float right, float bottom, float top);

        // Creates a frustum perspective matrix. Simulating glFrustum()
        // see. http://www.songho.ca/opengl/gl_projectionmatrix.html
        //		https://ksimek.github.io/2013/06/03/calibrated_cameras_in_opengl/
        mat4 frustum(float left, float right, float bottom, float top, float near, float far);

        // Creates a matrix for a right handed symmetric perspective-view frustum. Simulating gluPerspective().
        // fov_y: Specifies the field of view angle, in the y direction. Expressed in radians.
        // aspect: Specifies the aspect ratio that determines the field of view in the x direction. The
        //		   aspect ratio is the ratio of x (width) to y (height).
        // near: Specifies the distance from the viewer to the near clipping plane (always positive).
        // far:  Specifies the distance from the viewer to the far clipping plane (always positive).
        // NOTE: Degrees are an unhandy unit to work with. Thus I use radians for everything!
        // see https://ksimek.github.io/2013/06/18/calibrated-cameras-and-gluperspective/
        mat4 perspective(float fov_y, float aspect, float near, float far);
        mat4 perspective(float fov_y, float width, float height, float near, float far);

        // Creates a matrix for a symmetric perspective-view frustum with far plane at infinite.
        // fov_y: Specifies the field of view angle, in the y direction. Expressed in radians.
        // aspect: Specifies the aspect ratio that determines the field of view in the x direction. The
        //		   aspect ratio is the ratio of x (width) to y (height).
        // near: Specifies the distance from the viewer to the near clipping plane (always positive).
        mat4 infinite_perspective(float fov_y, float aspect, float near);

        // Creates a viewport matrix. Simulating glViewport().
        mat4 viewport(float width, float height);

        // Build a look at view matrix. Simulating gluLookAt()
        // eye: Position of the camera
        // center: Position where the camera is looking at
        // up: Normalized up vector, how the camera is oriented. Typically (0, 0, 1)
        mat4 look_at(const vec3& eye, const vec3& center, const vec3& up);

        // Define a picking region
        mat4 pick_matrix(const vec2& center, const vec2& delta, const vec4& viewport);

        // Map the specified object coordinates (obj.x, obj.y, obj.z) into window coordinates. Simulating gluProject()
        // obj: Specify the object coordinates.
        // model: Specifies the current model-view matrix
        // proj: Specifies the current projection matrix
        // viewport: Specifies the current viewport
        //				viewport[0] = 0;
        //				viewport[1] = 0;
        //				viewport[2] = screenWidth();
        //				viewport[3] = screenHeight();
        // OpenGL uses the lower corner for its origin while other softwares (e.g., Qt) may use upper corner
        // Return the computed window coordinates.
        vec3 project(const vec3& obj, const mat4& model, const mat4& proj, const int viewport[4], bool lowerleft = true);
        vec3 project(const vec3& obj, const mat4& mvp, const int viewport[4], bool lowerleft = true); // mvp = proj * model;

        // Map the specified window coordinates (win.x, win.y, win.z) into object coordinates. Simulating gluUnProject()
        // win: Specify the window coordinates to be mapped.
        // model: Specifies the model-view matrix
        // proj: Specifies the projection matrix
        // viewport: Specifies the viewport
        //				viewport[0] = 0;
        //				viewport[1] = 0;
        //				viewport[2] = screenWidth();
        //				viewport[3] = screenHeight();
        // OpenGL uses the lower corner for its origin while other softwares (e.g., Qt) may use upper corner
        // Returns the computed object coordinates.
        vec3 unproject(const vec3& win, const mat4& model, const mat4& proj, const int viewport[4], bool lowerleft = true);
        vec3 unproject(const vec3& win, const mat4& mvp, const int viewport[4], bool lowerleft = true); // mvp = proj * model;

        // --------------------------------------------------------------------------------------------------

        // Computes the normal matrix based on mat.
        // NOTE: this is NOT padded. Use the padded version in uniform blocks.
        mat3  normal_matrix(const mat4& mat);
        // Computes the normal matrix based on mat.
        // NOTE: this is the padded version suitable in uniform blocks.
        mat43 normal_matrix_padded(const mat4& mat);

    } // namespace transform

}


#endif  // EASY3D_TRANSFORM_H
