#include <easy3d/core/point_cloud.h>
#include <easy3d/core/property.h>
#include <easy3d/renderer/renderer.h>

#include <memory>
#include <typeinfo>
#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>


#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>, false)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*, false)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

// easy3d::PointCloud file:easy3d/core/point_cloud.h line:44
struct PyCallBack_easy3d_PointCloud : public easy3d::PointCloud {
	using easy3d::PointCloud::PointCloud;

	void property_stats(std::ostream & a0) const override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const easy3d::PointCloud *>(this), "property_stats");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PointCloud::property_stats(a0);
	}
	using _binder_ret_0 = std::vector<easy3d::vec3 > &;
	_binder_ret_0 points() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const easy3d::PointCloud *>(this), "points");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<_binder_ret_0>::value) {
				static pybind11::detail::override_caster_t<_binder_ret_0> caster;
				return pybind11::detail::cast_ref<_binder_ret_0>(std::move(o), caster);
			}
			return pybind11::detail::cast_safe<_binder_ret_0>(std::move(o));
		}
		return PointCloud::points();
	}
};

// easy3d::PointCloud::VertexProperty file:easy3d/core/point_cloud.h line:106
struct PyCallBack_easy3d_PointCloud_VertexProperty_easy3d_Vec_3_float_t : public easy3d::PointCloud::VertexProperty<easy3d::vec3> {
	using easy3d::PointCloud::VertexProperty<easy3d::vec3>::VertexProperty;

	using _binder_ret_0 = easy3d::vec3 &;
	_binder_ret_0 operator[](unsigned long a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const easy3d::PointCloud::VertexProperty<easy3d::vec3> *>(this), "__getitem__");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<_binder_ret_0>::value) {
				static pybind11::detail::override_caster_t<_binder_ret_0> caster;
				return pybind11::detail::cast_ref<_binder_ret_0>(std::move(o), caster);
			}
			return pybind11::detail::cast_safe<_binder_ret_0>(std::move(o));
		}
		return Property::operator[](a0);
	}
};

void bind_easy3d_core_point_cloud(pybind11::module_& m)
{
	{ // easy3d::PointCloud file:easy3d/core/point_cloud.h line:44
		pybind11::class_<easy3d::PointCloud, std::shared_ptr<easy3d::PointCloud>, PyCallBack_easy3d_PointCloud, easy3d::Model> cl(m, "PointCloud", "A data structure for point clouds.\n \n\n\n This implementation is inspired by Surface_mesh\n https://opensource.cit-ec.de/projects/surface_mesh");
		cl.def( pybind11::init( [](){ return new easy3d::PointCloud(); }, [](){ return new PyCallBack_easy3d_PointCloud(); } ) );
		cl.def( pybind11::init( [](PyCallBack_easy3d_PointCloud const &o){ return new PyCallBack_easy3d_PointCloud(o); } ) );
		cl.def( pybind11::init( [](easy3d::PointCloud const &o){ return new easy3d::PointCloud(o); } ) );

        // Initialization from a NumPy array or a list of points
        cl.def(pybind11::init([](pybind11::array_t<float> arr) {
            if (arr.ndim() != 2 || arr.shape(1) != 3) {
                throw std::invalid_argument("Input array must have shape (n, 3).");
            }
            auto buf = arr.unchecked<2>();
            auto pc = std::make_shared<easy3d::PointCloud>();
            for (ssize_t i = 0; i < arr.shape(0); ++i) {
                pc->add_vertex(easy3d::vec3(buf(i, 0), buf(i, 1), buf(i, 2)));
            }
            return pc;
        }), "Initialize PointCloud from a NumPy array with shape (n, 3)");

        // Add points to an existing PointCloud
        cl.def("add_points", [](easy3d::PointCloud &pc, pybind11::array_t<float> arr) {
            if (arr.ndim() != 2 || arr.shape(1) != 3) {
                throw std::invalid_argument("Input array must have shape (n, 3).");
            }
            auto buf = arr.unchecked<2>();
            for (ssize_t i = 0; i < arr.shape(0); ++i) {
                pc.add_vertex(easy3d::vec3(buf(i, 0), buf(i, 1), buf(i, 2)));
            }
        }, "Add multiple points to the PointCloud from a NumPy array with shape (n, 3)");

        cl.def("add_point", (struct easy3d::PointCloud::Vertex (easy3d::PointCloud::*)(const easy3d::vec3 &)) &easy3d::PointCloud::add_vertex, "add a new vertex with position \n\nC++: easy3d::PointCloud::add_vertex(const easy3d::vec3 &) --> struct easy3d::PointCloud::Vertex", pybind11::arg("p"));

        cl.def("add_point",
               [](easy3d::PointCloud &pc, pybind11::object point) {
                   if (pybind11::isinstance<easy3d::vec3>(point)) {
                       // If the input is an easy3d::vec3
                       pc.add_vertex(point.cast<easy3d::vec3>());
                   } else if (pybind11::isinstance<pybind11::iterable>(point)) {
                       // Convert iterable (like list) to NumPy array
                       auto iterable = point.cast<pybind11::iterable>();
                       std::vector<float> values;
                       for (auto item : iterable) {
                           values.push_back(item.cast<float>());
                       }

                       if (values.size() != 3) {
                           throw std::runtime_error("Iterable must contain exactly 3 elements.");
                       }

                       easy3d::vec3 v(values[0], values[1], values[2]);
                       pc.add_vertex(v);
                   } else if (pybind11::isinstance<pybind11::array_t<float>>(point)) {
                       // If the input is a NumPy array
                       pybind11::array_t<float> array = point.cast<pybind11::array_t<float>>();

                       // Check array shape
                       if (array.ndim() != 1 || array.shape(0) != 3) {
                           throw std::runtime_error("NumPy array must be a 1D array with 3 elements.");
                       }

                       auto buf = array.unchecked<1>(); // Access data buffer
                       easy3d::vec3 v(buf(0), buf(1), buf(2));
                       pc.add_vertex(v);
                   } else {
                       throw std::runtime_error(
                               "Input must be of type easy3d::vec3, a NumPy array with 3 elements, or a list/iterable with 3 elements."
                       );
                   }
               },
               "Adds a single point to the point cloud. Input can be easy3d::vec3, a NumPy array, or a list with 3 elements.",
               pybind11::arg("point"));

        // Retrieve all points as a NumPy array
        cl.def("to_numpy", [](const easy3d::PointCloud &pc) {
            // Create a NumPy array with shape (n_points, 3)
            std::vector<ssize_t> shape = {static_cast<ssize_t>(pc.n_vertices()), 3};
            pybind11::array_t<float> result(shape);  // Use a vector for the shape

            // Access the mutable buffer
            auto buf = result.mutable_unchecked<2>();
            for (size_t i = 0; i < pc.n_vertices(); ++i) {
                const auto &point = pc.points()[i];
                buf(i, 0) = point.x;
                buf(i, 1) = point.y;
                buf(i, 2) = point.z;
            }
            return result;
        }, "Convert the PointCloud to a NumPy array with shape (n, 3)");


        cl.def("name", [](easy3d::PointCloud& self) { return self.name(); }, pybind11::return_value_policy::copy, "Get the name of the point cloud.");
        cl.def("set_name", [](easy3d::PointCloud& self, const std::string& name) { self.set_name(name); }, "Set the name of the point cloud.");

        cl.def("renderer", [](const easy3d::PointCloud& self) -> const easy3d::Renderer* { return self.renderer(); }, pybind11::return_value_policy::reference_internal, "Returns the renderer of the model");
        cl.def("renderer", [](easy3d::PointCloud& self) -> easy3d::Renderer* { return self.renderer(); }, pybind11::return_value_policy::reference_internal, "Returns the renderer of the model");

        cl.def("assign", (class easy3d::PointCloud & (easy3d::PointCloud::*)(const class easy3d::PointCloud &)) &easy3d::PointCloud::operator=, "assign  to  performs a deep copy of all properties.\n\nC++: easy3d::PointCloud::operator=(const class easy3d::PointCloud &) --> class easy3d::PointCloud &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("__iadd__", (class easy3d::PointCloud & (easy3d::PointCloud::*)(const class easy3d::PointCloud &)) &easy3d::PointCloud::operator+=, "Merges another point cloud into the current one.\n Shifts the indices of vertices of the other point cloud by `number_of_vertices() + number_of_removed_vertices()`.\n Copies entries of all property maps which have the same name in both point clouds. That is, property maps which\n are only in `other` are ignored.\n Also copies elements which are marked as removed, and concatenates the freelists of both point clouds.\n\nC++: easy3d::PointCloud::operator+=(const class easy3d::PointCloud &) --> class easy3d::PointCloud &", pybind11::return_value_policy::automatic, pybind11::arg("other"));
		cl.def("join", (class easy3d::PointCloud & (easy3d::PointCloud::*)(const class easy3d::PointCloud &)) &easy3d::PointCloud::join, "Merges another point cloud into the current one.\n Shifts the indices of vertices of the other point cloud by `number_of_vertices() + number_of_removed_vertices()`.\n Copies entries of all property maps which have the same name in both point cloud. That is, property maps which\n are only in `other` are ignored.\n Also copies elements which are marked as removed, and concatenates the freelists of both point cloud.\n\nC++: easy3d::PointCloud::join(const class easy3d::PointCloud &) --> class easy3d::PointCloud &", pybind11::return_value_policy::automatic, pybind11::arg("other"));
		cl.def("assign", (class easy3d::PointCloud & (easy3d::PointCloud::*)(const class easy3d::PointCloud &)) &easy3d::PointCloud::assign, "assign  to  does not copy custom properties.\n\nC++: easy3d::PointCloud::assign(const class easy3d::PointCloud &) --> class easy3d::PointCloud &", pybind11::return_value_policy::automatic, pybind11::arg("rhs"));
		cl.def("vertices_size", (unsigned int (easy3d::PointCloud::*)() const) &easy3d::PointCloud::vertices_size, "returns number of (deleted and valid) vertices in the cloud\n\nC++: easy3d::PointCloud::vertices_size() const --> unsigned int");
		cl.def("n_vertices", (unsigned int (easy3d::PointCloud::*)() const) &easy3d::PointCloud::n_vertices, "returns number of vertices in the cloud\n\nC++: easy3d::PointCloud::n_vertices() const --> unsigned int");
		cl.def("clear", (void (easy3d::PointCloud::*)()) &easy3d::PointCloud::clear, "clear cloud: remove all vertices\n\nC++: easy3d::PointCloud::clear() --> void");
		cl.def("resize", (void (easy3d::PointCloud::*)(unsigned int)) &easy3d::PointCloud::resize, "resize space for vertices and their currently associated properties.\n\nC++: easy3d::PointCloud::resize(unsigned int) --> void", pybind11::arg("nv"));
		cl.def("has_garbage", (bool (easy3d::PointCloud::*)() const) &easy3d::PointCloud::has_garbage, "are there deleted vertices?\n\nC++: easy3d::PointCloud::has_garbage() const --> bool");
		cl.def("collect_garbage", (void (easy3d::PointCloud::*)()) &easy3d::PointCloud::collect_garbage, "remove deleted vertices\n\nC++: easy3d::PointCloud::collect_garbage() --> void");
		cl.def("delete_vertex", (void (easy3d::PointCloud::*)(struct easy3d::PointCloud::Vertex)) &easy3d::PointCloud::delete_vertex, "deletes the vertex  from the cloud\n\nC++: easy3d::PointCloud::delete_vertex(struct easy3d::PointCloud::Vertex) --> void", pybind11::arg("v"));
		cl.def("is_deleted", (bool (easy3d::PointCloud::*)(struct easy3d::PointCloud::Vertex) const) &easy3d::PointCloud::is_deleted, "returns whether vertex  is deleted\n \n\n collect_garbage()\n\nC++: easy3d::PointCloud::is_deleted(struct easy3d::PointCloud::Vertex) const --> bool", pybind11::arg("v"));
		cl.def("is_valid", (bool (easy3d::PointCloud::*)(struct easy3d::PointCloud::Vertex) const) &easy3d::PointCloud::is_valid, "return whether vertex  is valid, i.e. the index is stores it within the array bounds.\n\nC++: easy3d::PointCloud::is_valid(struct easy3d::PointCloud::Vertex) const --> bool", pybind11::arg("v"));
		cl.def("remove_vertex_property", (bool (easy3d::PointCloud::*)(const std::string &)) &easy3d::PointCloud::remove_vertex_property, "remove the vertex property named \n\nC++: easy3d::PointCloud::remove_vertex_property(const std::string &) --> bool", pybind11::arg("n"));
		cl.def("remove_model_property", (bool (easy3d::PointCloud::*)(const std::string &)) &easy3d::PointCloud::remove_model_property, "remove the model property named \n\nC++: easy3d::PointCloud::remove_model_property(const std::string &) --> bool", pybind11::arg("n"));
		cl.def("rename_vertex_property", (bool (easy3d::PointCloud::*)(const std::string &, const std::string &)) &easy3d::PointCloud::rename_vertex_property, "rename a vertex property given its name\n\nC++: easy3d::PointCloud::rename_vertex_property(const std::string &, const std::string &) --> bool", pybind11::arg("old_name"), pybind11::arg("new_name"));
		cl.def("rename_model_property", (bool (easy3d::PointCloud::*)(const std::string &, const std::string &)) &easy3d::PointCloud::rename_model_property, "rename a model property given its name\n\nC++: easy3d::PointCloud::rename_model_property(const std::string &, const std::string &) --> bool", pybind11::arg("old_name"), pybind11::arg("new_name"));
		cl.def("get_vertex_property_type", (const class std::type_info & (easy3d::PointCloud::*)(const std::string &) const) &easy3d::PointCloud::get_vertex_property_type, "get the type_info  of vertex property  returns an typeid(void)\n         if the property does not exist or if the type does not match. \n\nC++: easy3d::PointCloud::get_vertex_property_type(const std::string &) const --> const class std::type_info &", pybind11::return_value_policy::automatic, pybind11::arg("name"));
		cl.def("get_model_property_type", (const class std::type_info & (easy3d::PointCloud::*)(const std::string &) const) &easy3d::PointCloud::get_model_property_type, "get the type_info  of model property  returns an typeid(void)\n        if the property does not exist or if the type does not match. \n\nC++: easy3d::PointCloud::get_model_property_type(const std::string &) const --> const class std::type_info &", pybind11::return_value_policy::automatic, pybind11::arg("name"));
		cl.def("vertex_properties", (class std::vector<std::string> (easy3d::PointCloud::*)() const) &easy3d::PointCloud::vertex_properties, "returns the names of all vertex properties\n\nC++: easy3d::PointCloud::vertex_properties() const --> class std::vector<std::string>");
		cl.def("model_properties", (class std::vector<std::string> (easy3d::PointCloud::*)() const) &easy3d::PointCloud::model_properties, "returns the names of all model properties\n\nC++: easy3d::PointCloud::model_properties() const --> class std::vector<std::string>");
		cl.def("property_stats", (void (easy3d::PointCloud::*)(std::ostream &) const) &easy3d::PointCloud::property_stats, "prints the names of all properties to an output stream (e.g., std::cout)\n\nC++: easy3d::PointCloud::property_stats(std::ostream &) const --> void", pybind11::arg("output"));
		cl.def("vertices_begin", (class easy3d::PointCloud::VertexIterator (easy3d::PointCloud::*)() const) &easy3d::PointCloud::vertices_begin, "returns start iterator for vertices\n\nC++: easy3d::PointCloud::vertices_begin() const --> class easy3d::PointCloud::VertexIterator");
		cl.def("vertices_end", (class easy3d::PointCloud::VertexIterator (easy3d::PointCloud::*)() const) &easy3d::PointCloud::vertices_end, "returns end iterator for vertices\n\nC++: easy3d::PointCloud::vertices_end() const --> class easy3d::PointCloud::VertexIterator");
		cl.def("vertices", (class easy3d::PointCloud::VertexContainer (easy3d::PointCloud::*)() const) &easy3d::PointCloud::vertices, "returns vertex container for C++11 range-based for-loops\n\nC++: easy3d::PointCloud::vertices() const --> class easy3d::PointCloud::VertexContainer");
		cl.def("position", (easy3d::vec3 & (easy3d::PointCloud::*)(struct easy3d::PointCloud::Vertex)) &easy3d::PointCloud::position, "position of a vertex\n\nC++: easy3d::PointCloud::position(struct easy3d::PointCloud::Vertex) --> easy3d::vec3 &", pybind11::return_value_policy::automatic, pybind11::arg("v"));
		cl.def("points", (class std::vector<easy3d::vec3 > & (easy3d::PointCloud::*)()) &easy3d::PointCloud::points, "vector of vertex positions\n\nC++: easy3d::PointCloud::points() --> class std::vector<easy3d::vec3 > &", pybind11::return_value_policy::automatic);
        cl.def("points", (const class std::vector<easy3d::vec3 > & (easy3d::PointCloud::*)() const) &easy3d::PointCloud::points, "vector of vertex positions\n\nC++: easy3d::PointCloud::points() --> class std::vector<easy3d::vec3 > &", pybind11::return_value_policy::automatic);

        { // easy3d::PointCloud::BaseHandle file:easy3d/core/point_cloud.h line:52
		 	auto & enclosing_class = cl;
		 	pybind11::class_<easy3d::PointCloud::BaseHandle, std::shared_ptr<easy3d::PointCloud::BaseHandle>> cl(enclosing_class, "BaseHandle", "Base class for topology types (internally it is basically an index)\n \n\n Vertex");
		 	cl.def( pybind11::init( [](){ return new easy3d::PointCloud::BaseHandle(); } ), "doc" );
		 	cl.def( pybind11::init<int>(), pybind11::arg("_idx") );

		 	cl.def( pybind11::init( [](easy3d::PointCloud::BaseHandle const &o){ return new easy3d::PointCloud::BaseHandle(o); } ) );
		 	cl.def("idx", (int (easy3d::PointCloud::BaseHandle::*)() const) &easy3d::PointCloud::BaseHandle::idx, "Get the underlying index of this handle\n\nC++: easy3d::PointCloud::BaseHandle::idx() const --> int");
		 	cl.def("reset", (void (easy3d::PointCloud::BaseHandle::*)()) &easy3d::PointCloud::BaseHandle::reset, "reset handle to be invalid (index=-1)\n\nC++: easy3d::PointCloud::BaseHandle::reset() --> void");
		 	cl.def("is_valid", (bool (easy3d::PointCloud::BaseHandle::*)() const) &easy3d::PointCloud::BaseHandle::is_valid, "return whether the handle is valid, i.e., the index is not equal to -1.\n\nC++: easy3d::PointCloud::BaseHandle::is_valid() const --> bool");
		 	cl.def("__eq__", (bool (easy3d::PointCloud::BaseHandle::*)(const class easy3d::PointCloud::BaseHandle &) const) &easy3d::PointCloud::BaseHandle::operator==, "are two handles equal?\n\nC++: easy3d::PointCloud::BaseHandle::operator==(const class easy3d::PointCloud::BaseHandle &) const --> bool", pybind11::arg("_rhs"));
		 	cl.def("__ne__", (bool (easy3d::PointCloud::BaseHandle::*)(const class easy3d::PointCloud::BaseHandle &) const) &easy3d::PointCloud::BaseHandle::operator!=, "are two handles different?\n\nC++: easy3d::PointCloud::BaseHandle::operator!=(const class easy3d::PointCloud::BaseHandle &) const --> bool", pybind11::arg("_rhs"));

		 	{ // easy3d::PointCloud::BaseHandle::Hash file:easy3d/core/point_cloud.h line:84
		 		auto & enclosing_class = cl;
		 		pybind11::class_<easy3d::PointCloud::BaseHandle::Hash, std::shared_ptr<easy3d::PointCloud::BaseHandle::Hash>> cl(enclosing_class, "Hash", "helper structure to be able to use std::unordered_map");
		 		cl.def( pybind11::init( [](){ return new easy3d::PointCloud::BaseHandle::Hash(); } ) );
		 		cl.def("__call__", (std::size_t (easy3d::PointCloud::BaseHandle::Hash::*)(const class easy3d::PointCloud::BaseHandle &) const) &easy3d::PointCloud::BaseHandle::Hash::operator(), "C++: easy3d::PointCloud::BaseHandle::Hash::operator()(const class easy3d::PointCloud::BaseHandle &) const --> std::size_t", pybind11::arg("h"));
		 	}

		 }

		 { // easy3d::PointCloud::Vertex file:easy3d/core/point_cloud.h line:95
		 	auto & enclosing_class = cl;
		 	pybind11::class_<easy3d::PointCloud::Vertex, std::shared_ptr<easy3d::PointCloud::Vertex>, easy3d::PointCloud::BaseHandle> cl(enclosing_class, "Vertex", "this type represents a vertex (internally it is basically an index)");
		 	cl.def( pybind11::init( [](){ return new easy3d::PointCloud::Vertex(); } ), "doc" );
		 	cl.def( pybind11::init<int>(), pybind11::arg("_idx") );

		 	cl.def( pybind11::init( [](easy3d::PointCloud::Vertex const &o){ return new easy3d::PointCloud::Vertex(o); } ) );
		 	cl.def("__lshift__", (std::ostream & (easy3d::PointCloud::Vertex::*)(std::ostream &) const) &easy3d::PointCloud::Vertex::operator<<, "C++: easy3d::PointCloud::Vertex::operator<<(std::ostream &) const --> std::ostream &", pybind11::return_value_policy::automatic, pybind11::arg("os"));
		 }

		 { // easy3d::PointCloud::VertexProperty file:easy3d/core/point_cloud.h line:106
		 	auto & enclosing_class = cl;
		 	pybind11::class_<easy3d::PointCloud::VertexProperty<bool>, std::shared_ptr<easy3d::PointCloud::VertexProperty<bool>>, easy3d::Property<bool> > cl(enclosing_class, "VertexProperty_bool_t", "");
		 	cl.def( pybind11::init( [](){ return new easy3d::PointCloud::VertexProperty<bool>(); } ) );
		 	cl.def( pybind11::init<class easy3d::Property<bool> >(), pybind11::arg("p") );

		 	cl.def( pybind11::init( [](easy3d::PointCloud::VertexProperty<bool> const &o){ return new easy3d::PointCloud::VertexProperty<bool>(o); } ) );
		 	cl.def("assign", (class easy3d::PointCloud::VertexProperty<bool> & (easy3d::PointCloud::VertexProperty<bool>::*)(const class easy3d::PointCloud::VertexProperty<bool> &)) &easy3d::PointCloud::VertexProperty<bool>::operator=, "C++: easy3d::PointCloud::VertexProperty<bool>::operator=(const class easy3d::PointCloud::VertexProperty<bool> &) --> class easy3d::PointCloud::VertexProperty<bool> &", pybind11::return_value_policy::automatic, pybind11::arg(""));
		 	cl.def("reset", (void (easy3d::Property<bool>::*)()) &easy3d::Property<bool>::reset, "C++: easy3d::Property<bool>::reset() --> void");
		 	cl.def("data", (const bool * (easy3d::Property<bool>::*)() const) &easy3d::Property<bool>::data, "C++: easy3d::Property<bool>::data() const --> const bool *", pybind11::return_value_policy::automatic);
		 	cl.def("vector", (class std::vector<bool> & (easy3d::Property<bool>::*)()) &easy3d::Property<bool>::vector, "C++: easy3d::Property<bool>::vector() --> class std::vector<bool> &", pybind11::return_value_policy::automatic);
		 	cl.def("array", (class easy3d::PropertyArray<bool> & (easy3d::Property<bool>::*)()) &easy3d::Property<bool>::array, "C++: easy3d::Property<bool>::array() --> class easy3d::PropertyArray<bool> &", pybind11::return_value_policy::automatic);
		 	cl.def("name", (const std::string & (easy3d::Property<bool>::*)() const) &easy3d::Property<bool>::name, "C++: easy3d::Property<bool>::name() const --> const std::string &", pybind11::return_value_policy::automatic);
		 	cl.def("set_name", (void (easy3d::Property<bool>::*)(const std::string &)) &easy3d::Property<bool>::set_name, "C++: easy3d::Property<bool>::set_name(const std::string &) --> void", pybind11::arg("n"));
		 	cl.def("assign", (class easy3d::Property<bool> & (easy3d::Property<bool>::*)(const class easy3d::Property<bool> &)) &easy3d::Property<bool>::operator=, "C++: easy3d::Property<bool>::operator=(const class easy3d::Property<bool> &) --> class easy3d::Property<bool> &", pybind11::return_value_policy::automatic, pybind11::arg(""));
		 }

		 { // easy3d::PointCloud::VertexProperty file:easy3d/core/point_cloud.h line:106
		 	auto & enclosing_class = cl;
		 	pybind11::class_<easy3d::PointCloud::VertexProperty<easy3d::vec3>, std::shared_ptr<easy3d::PointCloud::VertexProperty<easy3d::vec3>>, PyCallBack_easy3d_PointCloud_VertexProperty_easy3d_Vec_3_float_t, easy3d::Property<easy3d::vec3>> cl(enclosing_class, "VertexProperty_easy3d_Vec_3_float_t", "");
		 	cl.def( pybind11::init( [](){ return new easy3d::PointCloud::VertexProperty<easy3d::vec3>(); }, [](){ return new PyCallBack_easy3d_PointCloud_VertexProperty_easy3d_Vec_3_float_t(); } ) );
		 	cl.def( pybind11::init<class easy3d::Property<easy3d::vec3 >>(), pybind11::arg("p") );

		 	cl.def( pybind11::init( [](PyCallBack_easy3d_PointCloud_VertexProperty_easy3d_Vec_3_float_t const &o){ return new PyCallBack_easy3d_PointCloud_VertexProperty_easy3d_Vec_3_float_t(o); } ) );
		 	cl.def( pybind11::init( [](easy3d::PointCloud::VertexProperty<easy3d::vec3> const &o){ return new easy3d::PointCloud::VertexProperty<easy3d::vec3>(o); } ) );
		 	cl.def("__getitem__", (easy3d::vec3 & (easy3d::PointCloud::VertexProperty<easy3d::vec3>::*)(struct easy3d::PointCloud::Vertex)) &easy3d::PointCloud::VertexProperty<easy3d::vec3>::operator[], "C++: easy3d::PointCloud::VertexProperty<easy3d::vec3>::operator[](struct easy3d::PointCloud::Vertex) --> easy3d::vec3 &", pybind11::return_value_policy::automatic, pybind11::arg("v"));
		 	cl.def("assign", (class easy3d::PointCloud::VertexProperty<easy3d::vec3 > & (easy3d::PointCloud::VertexProperty<easy3d::vec3>::*)(const class easy3d::PointCloud::VertexProperty<easy3d::vec3 > &)) &easy3d::PointCloud::VertexProperty<easy3d::vec3>::operator=, "C++: easy3d::PointCloud::VertexProperty<easy3d::vec3>::operator=(const class easy3d::PointCloud::VertexProperty<easy3d::vec3 > &) --> class easy3d::PointCloud::VertexProperty<easy3d::vec3 > &", pybind11::return_value_policy::automatic, pybind11::arg(""));
		 	cl.def("reset", (void (easy3d::Property<easy3d::vec3>::*)()) &easy3d::Property<easy3d::vec3>::reset, "C++: easy3d::Property<easy3d::vec3>::reset() --> void");
		 	cl.def("__getitem__", (easy3d::vec3 & (easy3d::Property<easy3d::vec3>::*)(unsigned long)) &easy3d::Property<easy3d::vec3>::operator[], "C++: easy3d::Property<easy3d::vec3>::operator[](unsigned long) --> easy3d::vec3 &", pybind11::return_value_policy::automatic, pybind11::arg("i"));
		 	cl.def("data", (const easy3d::vec3 * (easy3d::Property<easy3d::vec3>::*)() const) &easy3d::Property<easy3d::vec3>::data, "C++: easy3d::Property<easy3d::vec3>::data() const --> const easy3d::vec3 *", pybind11::return_value_policy::automatic);
		 	cl.def("vector", (class std::vector<easy3d::vec3 > & (easy3d::Property<easy3d::vec3>::*)()) &easy3d::Property<easy3d::vec3>::vector, "C++: easy3d::Property<easy3d::vec3>::vector() --> class std::vector<easy3d::vec3 > &", pybind11::return_value_policy::automatic);
		 	cl.def("array", (class easy3d::PropertyArray<easy3d::vec3 > & (easy3d::Property<easy3d::vec3>::*)()) &easy3d::Property<easy3d::vec3>::array, "C++: easy3d::Property<easy3d::vec3>::array() --> class easy3d::PropertyArray<easy3d::vec3 > &", pybind11::return_value_policy::automatic);
		 	cl.def("name", (const std::string & (easy3d::Property<easy3d::vec3>::*)() const) &easy3d::Property<easy3d::vec3>::name, "C++: easy3d::Property<easy3d::vec3>::name() const --> const std::string &", pybind11::return_value_policy::automatic);
		 	cl.def("set_name", (void (easy3d::Property<easy3d::vec3>::*)(const std::string &)) &easy3d::Property<easy3d::vec3>::set_name, "C++: easy3d::Property<easy3d::vec3>::set_name(const std::string &) --> void", pybind11::arg("n"));
		 	cl.def("assign", (class easy3d::Property<easy3d::vec3 > & (easy3d::Property<easy3d::vec3>::*)(const class easy3d::Property<easy3d::vec3 > &)) &easy3d::Property<easy3d::vec3>::operator=, "C++: easy3d::Property<easy3d::vec3>::operator=(const class easy3d::Property<easy3d::vec3 > &) --> class easy3d::Property<easy3d::vec3 > &", pybind11::return_value_policy::automatic, pybind11::arg(""));
		 }

		 { // easy3d::PointCloud::VertexIterator file:easy3d/core/point_cloud.h line:157
		 	auto & enclosing_class = cl;
		 	pybind11::class_<easy3d::PointCloud::VertexIterator, std::shared_ptr<easy3d::PointCloud::VertexIterator>> cl(enclosing_class, "VertexIterator", "this class iterates linearly over all vertices\n \n\n vertices_begin(), vertices_end()");
		 	cl.def( pybind11::init( [](){ return new easy3d::PointCloud::VertexIterator(); } ), "doc" );
		 	cl.def( pybind11::init( [](struct easy3d::PointCloud::Vertex const & a0){ return new easy3d::PointCloud::VertexIterator(a0); } ), "doc" , pybind11::arg("v"));
		 	cl.def( pybind11::init<struct easy3d::PointCloud::Vertex, const class easy3d::PointCloud *>(), pybind11::arg("v"), pybind11::arg("m") );

		 	cl.def( pybind11::init( [](easy3d::PointCloud::VertexIterator const &o){ return new easy3d::PointCloud::VertexIterator(o); } ) );
		 	cl.def("dereference", (struct easy3d::PointCloud::Vertex (easy3d::PointCloud::VertexIterator::*)() const) &easy3d::PointCloud::VertexIterator::operator*, "get the vertex the iterator refers to\n\nC++: easy3d::PointCloud::VertexIterator::operator*() const --> struct easy3d::PointCloud::Vertex");
		 	cl.def("__eq__", (bool (easy3d::PointCloud::VertexIterator::*)(const class easy3d::PointCloud::VertexIterator &) const) &easy3d::PointCloud::VertexIterator::operator==, "are two iterators equal?\n\nC++: easy3d::PointCloud::VertexIterator::operator==(const class easy3d::PointCloud::VertexIterator &) const --> bool", pybind11::arg("rhs"));
		 	cl.def("__ne__", (bool (easy3d::PointCloud::VertexIterator::*)(const class easy3d::PointCloud::VertexIterator &) const) &easy3d::PointCloud::VertexIterator::operator!=, "are two iterators different?\n\nC++: easy3d::PointCloud::VertexIterator::operator!=(const class easy3d::PointCloud::VertexIterator &) const --> bool", pybind11::arg("rhs"));
		 	cl.def("pre_increment", (class easy3d::PointCloud::VertexIterator & (easy3d::PointCloud::VertexIterator::*)()) &easy3d::PointCloud::VertexIterator::operator++, "pre-increment iterator\n\nC++: easy3d::PointCloud::VertexIterator::operator++() --> class easy3d::PointCloud::VertexIterator &", pybind11::return_value_policy::automatic);
		 	cl.def("pre_decrement", (class easy3d::PointCloud::VertexIterator & (easy3d::PointCloud::VertexIterator::*)()) &easy3d::PointCloud::VertexIterator::operator--, "pre-decrement iterator\n\nC++: easy3d::PointCloud::VertexIterator::operator--() --> class easy3d::PointCloud::VertexIterator &", pybind11::return_value_policy::automatic);
		 }

		 { // easy3d::PointCloud::VertexContainer file:easy3d/core/point_cloud.h line:211
		 	auto & enclosing_class = cl;
		 	pybind11::class_<easy3d::PointCloud::VertexContainer, std::shared_ptr<easy3d::PointCloud::VertexContainer>> cl(enclosing_class, "VertexContainer", "this helper class is a container for iterating through all\n vertices using C++11 range-based for-loops.\n \n\n vertices()");
		 	cl.def( pybind11::init<class easy3d::PointCloud::VertexIterator, class easy3d::PointCloud::VertexIterator>(), pybind11::arg("_begin"), pybind11::arg("_end") );

		 	cl.def( pybind11::init( [](easy3d::PointCloud::VertexContainer const &o){ return new easy3d::PointCloud::VertexContainer(o); } ) );
		 	cl.def("begin", (class easy3d::PointCloud::VertexIterator (easy3d::PointCloud::VertexContainer::*)() const) &easy3d::PointCloud::VertexContainer::begin, "C++: easy3d::PointCloud::VertexContainer::begin() const --> class easy3d::PointCloud::VertexIterator");
		 	cl.def("end", (class easy3d::PointCloud::VertexIterator (easy3d::PointCloud::VertexContainer::*)() const) &easy3d::PointCloud::VertexContainer::end, "C++: easy3d::PointCloud::VertexContainer::end() const --> class easy3d::PointCloud::VertexIterator");
		 }

	}
}
