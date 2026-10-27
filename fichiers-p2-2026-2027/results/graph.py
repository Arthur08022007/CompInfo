import sys
import os
import numpy as np
import matplotlib.pyplot as plt

def generer_graphe(chemin_fichier):
    # 1. Vérifier si le fichier existe
    if not os.path.exists(chemin_fichier):
        print(f"Erreur : Le fichier '{chemin_fichier}' n'existe pas.")
        return

    # 2. Charger les données de vitesse depuis le fichier
    try:
        vitesses = np.loadtxt(chemin_fichier)
    except Exception as e:
        print(f"Erreur lors de la lecture du fichier : {e}")
        return

    # 3. Création de la figure
    plt.figure(figsize=(10, 6))

    # 4. Tracer l'histogramme des données réelles (normalisé avec density=True)
    # On définit des intervalles (bins) d'une largeur de 0.2 allant de 0 à 2.4
    intervalles = np.arange(0, 2.6, 0.1)
    plt.hist(vitesses, bins=intervalles, density=True, alpha=0.6, 
             color='#3498db', edgecolor='black', label='Données réelles (Histogramme)')

    # 5. Tracer la courbe théorique de Maxwell-Boltzmann
    # Formule pour m = 1 et k_B*T = 0.5 : f(v) = 2 * v * exp(-v^2)
    v_theorique = np.linspace(0, 2.5, 500)
    f_v = 2 * v_theorique * np.exp(-v_theorique**2)
    
    plt.plot(v_theorique, f_v, color='#e74c3c', linewidth=2.5, 
             label='Courbe théorique : $2v \\cdot e^{-v^2}$')

    # 6. Habillage et mise en forme du graphique
    plt.title('Distribution des vitesses de particules\n(Maxwell-Boltzmann pour $m=1$ et $k_B T=0.5$)', 
              fontsize=14, fontweight='bold', pad=15)
    plt.xlabel('Vitesse $v$', fontsize=12)
    plt.ylabel('Densité de probabilité $f(v)$', fontsize=12)
    plt.xlim(0, 2.6)
    plt.grid(True, linestyle='--', alpha=0.5)
    plt.legend(fontsize=11)

    # 7. Affichage du graphique
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    # Vérifier qu'un fichier a bien été passé en argument de ligne de commande
    if len(sys.argv) < 2:
        print("Usage: python graphe_vitesse.py <chemin_du_fichier_vitesse.txt>")
    else:
        generer_graphe(sys.argv[1])
