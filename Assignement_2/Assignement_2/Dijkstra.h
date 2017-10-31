#ifndef DIJKSTRA_H
#define DIJKSTRA_H

class CVertexC;

size_t FindPathLength(CVertexC* inStartVertex, const size_t vertex_count);

size_t FindDFS(CVertexC* inDestVertex, const size_t inVertexCount, const size_t inWayFarerCount);

#endif // DIJKSTRA_H
