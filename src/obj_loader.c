#include "../include/header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// v = vertex
// f = face
// faces use multiple time the same vertex
u8 load_obj() {
  FILE *fp = fopen("models/teapot.obj", "r");
  if (fp == NULL) {
    fprintf(stderr, "FP NULL\n");
    return 0;
  }
  char buffer[128];
  // char tmp;
  vec3 *verts = NULL;
  // triangle *mesh = NULL;
  int vertCount = 0;
  // int meshSize = 0;

  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    if (buffer[0] == 'v') {
      vec3 vert;
      sscanf(buffer, "v %lf %lf %lf", &vert.x, &vert.y, &vert.z);

      verts = realloc(verts, (vertCount + 1) * sizeof(vec3));
      verts[vertCount++] = vert;
    } else if (buffer[0] == 'f') {
      triangle tri;
      int f[3];

      // get the points indexes in the vertex array:
      sscanf(buffer, "f %d %d %d", &f[0], &f[1], &f[2]);

      // create a triangle and add it to the tri array:
      mesh = realloc(mesh, (meshSize + 1) * sizeof(triangle));
      tri.p[0] = verts[f[0] - 1];
      tri.p[1] = verts[f[1] - 1];
      tri.p[2] = verts[f[2] - 1];
      // printf("f %d %d %d\n", f[0], f[1], f[2]);
      mesh[meshSize++] = tri;
    }
  }

  fclose(fp);

  // Afficher les vertices
  printf("Vertices:\n");
  // for (int i = 0; i < vertCount; ++i) {
  //   printf("v %f %f %f\n", verts[i].x, verts[i].y, verts[i].z);
  // }
  //
  // // Afficher les faces
  printf("Faces:\n");
  // for (int i = 0; i < meshSize; ++i) {
  //   printf("f {%f, %f, %f}; {%f, %f, %f}; {%f, %f, %f}\n", mesh[i].p[0].x,
  //          mesh[i].p[0].y, mesh[i].p[0].z, mesh[i].p[1].x, mesh[i].p[1].y,
  //          mesh[i].p[1].z, mesh[i].p[2].x, mesh[i].p[2].y, mesh[i].p[2].z);
  // }

  printf("triCount: %d\n", meshSize);
  // for (int i = 0; i < triCount; i++) {
  //   triangle tri = tris[i];
  //   stack_push(&mesh, tri);
  // }
  // printf("stack count: %d\n", mesh.count);

  // Libérer la mémoire
  free(verts);

  return 1;
}
