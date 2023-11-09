#include "terrain_factorial_generation.h"
#include "utils.h"
#include <iostream>

FactorialTerrainGeneration::FactorialTerrainGeneration(int cols, int rows, int iterations, float min_height, float max_height) {
    this->rows =  rows;
    this->cols = cols;

    init_x_z();
    float delta_height = max_height - min_height;
    LinearInterpolator interpolator(0.0f, 255.0f, 0.0f, 1.0f);

    for(int i = 0; i < iterations; i += 1) {
        glm::vec3 point1 = generate_ramdom_point(cols, rows);
        glm::vec3 point2;

        bool different_points = false;

        while(!different_points) {
            point2 = generate_ramdom_point(cols, rows);

            if(point1 != point2)
                different_points = true;

        }

        float iteration_ratio = (float)i/ (float) iterations;
        float height = max_height - iteration_ratio * delta_height;

        glm::vec3 main_dir = point2 - point1;



        for(int z = 0; z < rows; z += 1) {
            for(int x = 0; x < cols; x += 1) {

                glm::vec3 current_dir = glm::vec3(
                        x -   point2.x,
                        0.0f,
                        z -   point2.z
                        );

                float cross_product = main_dir.x - current_dir.z * current_dir.z - current_dir.x;

                if(cross_product > 0.0f) {
                    Vertex vertex = get_vertex(x, z);
                    vertex.position.y = interpolator.map(height);
                    set_vertex(x, z, vertex);

                }

            }
        }




    }

    //init_mesh();


}

FactorialTerrainGeneration::~FactorialTerrainGeneration() {

}
