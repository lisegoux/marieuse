import gmsh

# Initialisation de GMSH
gmsh.initialize()

# Créer un modèle géométrique
gmsh.model.add("forme_complexe")

# Définir les points
points = [
    (0, 0), (6, 0), (6, 3), (1, 3), (1, 4), 
    (6, 4), (6, 10), (5, 10), (5, 5), (0, 5),
    (0, 2), (5, 2), (5, 1), (0, 1), (0, 0)
]

point_ids = []
lc = 0.1

# Ajouter les points dans GMSH
for x, y in points:
    point_ids.append(gmsh.model.geo.addPoint(x, y, 0, lc))


# Créer les lignes entre les points consécutifs
lines = []
for i in range(len(point_ids) - 1):
    lines.append(gmsh.model.geo.addLine(point_ids[i], point_ids[i+1]))

# Boucle pour fermer la forme (relier le dernier point au premier)
lines.append(gmsh.model.geo.addLine(point_ids[-1], point_ids[0]))

# Créer la surface de la forme
curve_loop = gmsh.model.geo.addCurveLoop(lines)
surface = gmsh.model.geo.addPlaneSurface([curve_loop])

# Synchroniser la géométrie
gmsh.model.geo.synchronize()

# Générer le maillage
gmsh.model.mesh.generate(2)

# Sauvegarder le fichier de maillage
gmsh.write("forme_complexe.msh")

# Modifier la couleur du maillage via la fenêtre graphique de GMSH
# Utilise 'View[0].ElementColor' pour ajuster les couleurs de la vue graphique
# Ceci n'est pas fait directement via `gmsh.option.setNumber`, mais plutôt dans l'interface graphique.

# Afficher le modèle dans l'interface GMSH avec le maillage
gmsh.fltk.run()

# Finaliser GMSH
gmsh.finalize()
