#include "../include/mesh.h"
#include <stdio.h>

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
  vec3 *verts = NULL;
  int vertCount = 0;

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
      Mesh.mesh = realloc(Mesh.mesh, (Mesh.meshSize + 1) * sizeof(triangle));
      tri.p[0] = verts[f[0] - 1];
      tri.p[1] = verts[f[1] - 1];
      tri.p[2] = verts[f[2] - 1];
      // printf("f %d %d %d\n", f[0], f[1], f[2]);
      Mesh.mesh[Mesh.meshSize++] = tri;
    }
  }

  fclose(fp);

  printf("triCount: %d\n", Mesh.meshSize);
  free(verts);
  return 1;
}
