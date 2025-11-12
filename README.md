# 🌳 Blocky Trees

**Course**: CPSC221, UBC, Introduction to data structures and algorithms

**Desc**: Image processing/compression using **ternary space-partitioning trees** (ThreeTree). The project involves constructing a recursive tree structure where nodes represent rectangular image regions and are built until a specified **color variability tolerance** is met, achieving a form of **lossy image compression**.

**Algorithms Used:**

- **Complex Recursion (Divide and Conquer)**: Used extensively in the ThreeTree's BuildTree and helper functions (Size, Render, etc.) to recursively split image regions into up to three smaller parts.

- **Dynamic Programming (2D Prefix Sums)**: The Stats class uses Summed-Area Tables (2D prefix sum arrays) to pre-calculate color channel sums/sum-of-squares in O(w⋅h) time, allowing the average color and variability of any rectangular region to be queried efficiently in O(1) time.

- **Spatial Partitioning**: The core algorithm partitions a 2D image space based on color variability, similar to a Quadtree, but using three partitions per split.

**Data Structures Used:**

- Ternary Tree (ThreeTree): The central custom data structure where each node can have 0, 2, or 3 children, representing a recursive split of the image.

- Dynamic Arrays (Vectors): Standard implementation components for storing data within the Stats class (the 2D prefix sum arrays) and likely used internally by the PNG image object.

- Pairs/Tuples (Coordinate System): Used to manage and pass upper-left coordinates (x,y) of image regions.

- Test
