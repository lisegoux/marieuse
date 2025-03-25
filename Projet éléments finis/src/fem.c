#include "fem.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    double x, y;
} Node;

typedef struct {
    int id;
    int type; // 3 pour triangle, 4 pour quadrilatère
    int nodes[4]; // Max 4 pour quadrilatères
} Element;

typedef struct {
    int numNodes;
    int numElements;
    Node *nodes;
    Element *elements;
} Mesh;

typedef struct {
    double E;  // Module d'élasticité
    double nu; // Coefficient de Poisson
    int numForces;
    int *forceNodes;
    double *Fx, *Fy;
    int numBC;
    int *bcNodes;
    double *Ux, *Uy;
} Problem;

/* ==================== Lecture du maillage ==================== */
void read_mesh(const char *filename, Mesh *mesh) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erreur ouverture mesh.txt");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", &mesh->numNodes);
    mesh->nodes = malloc(mesh->numNodes * sizeof(Node));

    for (int i = 0; i < mesh->numNodes; i++) {
        fscanf(file, "%d %lf %lf", &mesh->nodes[i].id, &mesh->nodes[i].x, &mesh->nodes[i].y);
    }

    fscanf(file, "%d", &mesh->numElements);
    mesh->elements = malloc(mesh->numElements * sizeof(Element));

    for (int i = 0; i < mesh->numElements; i++) {
        fscanf(file, "%d %d %d %d %d", &mesh->elements[i].id, &mesh->elements[i].type, 
               &mesh->elements[i].nodes[0], &mesh->elements[i].nodes[1], &mesh->elements[i].nodes[2]);
    }

    fclose(file);
}

/* ==================== Lecture du problème ==================== */
void read_problem(const char *filename, Problem *problem) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erreur ouverture problem.txt");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "E = %lf", &problem->E);
    fscanf(file, "nu = %lf", &problem->nu);

    fscanf(file, "%d", &problem->numForces);
    problem->forceNodes = malloc(problem->numForces * sizeof(int));
    problem->Fx = malloc(problem->numForces * sizeof(double));
    problem->Fy = malloc(problem->numForces * sizeof(double));

    for (int i = 0; i < problem->numForces; i++) {
        fscanf(file, "%d %lf %lf", &problem->forceNodes[i], &problem->Fx[i], &problem->Fy[i]);
    }

    fscanf(file, "%d", &problem->numBC);
    problem->bcNodes = malloc(problem->numBC * sizeof(int));
    problem->Ux = malloc(problem->numBC * sizeof(double));
    problem->Uy = malloc(problem->numBC * sizeof(double));

    for (int i = 0; i < problem->numBC; i++) {
        fscanf(file, "%d %lf %lf", &problem->bcNodes[i], &problem->Ux[i], &problem->Uy[i]);
    }

    fclose(file);
}

/* ==================== Libération de la mémoire ==================== */
void free_mesh(Mesh *mesh) {
    free(mesh->nodes);
    free(mesh->elements);
}

void free_problem(Problem *problem) {
    free(problem->forceNodes);
    free(problem->Fx);
    free(problem->Fy);
    free(problem->bcNodes);
    free(problem->Ux);
    free(problem->Uy);
}

/* ==================== Fonction principale ==================== */
int main(int argc, char *argv[]) {
    const char *meshFile = "data/mesh.txt";
    const char *problemFile = "data/problem.txt";

    if (argc > 2) {
        meshFile = argv[1];
        problemFile = argv[2];
    }

    Mesh mesh;
    Problem problem;

    read_mesh(meshFile, &mesh);
    read_problem(problemFile, &problem);

    printf("Maillage et problème chargés avec succès !\n");

    free_mesh(&mesh);
    free_problem(&problem);

    return 0;
}

