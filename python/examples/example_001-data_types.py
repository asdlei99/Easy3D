# -------------------------------------------------------------------------------
# Example: Demonstrating vec2, vec3, and vec4
# -------------------------------------------------------------------------------
# This script demonstrates how to use the Easy3D vector classes:
# - `vec2`: Represents 2D points
# - `vec3`: Represents 3D points
# - `vec4`: Represents 4D points
# The script shows how to create these objects and convert them to NumPy arrays
# for easy manipulation in Python.
# -------------------------------------------------------------------------------

# -------------------------------------------------------------------------------
# Adding Easy3D Python Bindings to the System Path
# -------------------------------------------------------------------------------
# This is required if the bindings are not installed via `pip` but are located in
# a local build directory. To install the bindings, use the following command:
#       "pip install YOUR_BUILD_DIRECTORY/lib/python/setup.py"
# -------------------------------------------------------------------------------
import sys
sys.path.append("../../cmake-build-debug/lib/python")

# -------------------------------------------------------------------------------
# Importing Necessary Libraries
# -------------------------------------------------------------------------------
import easy3d           # Easy3D library for 3D visualization and processing
import numpy as np      # NumPy library (used for handling data)

# -------------------------------------------------------------------------------
# Initializing Easy3D
# -------------------------------------------------------------------------------
# The `easy3d.initialize(True)` function initializes the Easy3D library.
# The `True` parameter enables detailed logging, which is useful for debugging.
easy3d.initialize(True)

# -------------------------------------------------------------------------------
# Creating and Converting a vec2 Object
# -------------------------------------------------------------------------------
# A `vec2` object represents a 2D point. We create a `vec2` object using two values.
# Optionally, the object can also be created using a list: `vec2([x, y])`.
v2 = easy3d.vec2(2.0, 2.0)              # or v2 = easy3d.vec2([2.0, 2.0])

# The `to_numpy()` method converts the `vec2` object into a NumPy array.
np_v2 = v2.to_numpy()  # Convert to NumPy array

# Output the NumPy array representation of the `vec2` object.
print("vec2 as NumPy array:", np_v2)    # Output: [2. 2.]

# -------------------------------------------------------------------------------
# Creating and Converting a vec3 Object
# -------------------------------------------------------------------------------
# A `vec3` object represents a 3D point. We create a `vec3` object using three values.
# Optionally, the object can also be created using a list: `vec3([x, y, z])`.
v3 = easy3d.vec3(3.0, 3.0, 3.0)         # or v3 = easy3d.vec3([3.0, 3.0, 3.0])

# The `to_numpy()` method converts the `vec3` object into a NumPy array.
np_v3 = v3.to_numpy()  # Convert to NumPy array

# Output the NumPy array representation of the `vec3` object.
print("vec3 as NumPy array:", np_v3)    # Output: [3. 3. 3.]

# -------------------------------------------------------------------------------
# Creating and Converting a vec4 Object
# -------------------------------------------------------------------------------
# A `vec4` object represents a 4D point. We create a `vec4` object using four values.
# Optionally, the object can also be created using a list: `vec4([x, y, z, w])`.
v4 = easy3d.vec4(4.0, 4.0, 4.0, 4.0)    # or v4 = easy3d.vec4([4.0, 4.0, 4.0, 4.0])

# The `to_numpy()` method converts the `vec4` object into a NumPy array.
np_v4 = v4.to_numpy()                   # Convert to NumPy array

# Output the NumPy array representation of the `vec4` object.
print("vec4 as NumPy array:", np_v4)    # Output: [4. 4. 4. 4.]
