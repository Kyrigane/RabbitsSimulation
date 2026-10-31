import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

# Configuration du style visuel
sns.set_theme(style="whitegrid")
plt.figure(figsize=(10, 6))

# Chargement des données d'évolution et des statistiques
df = pd.read_csv("resultats.csv")
df_stats = pd.read_csv("stats.csv")

# Calcul des statistiques globales
simulations_reussies = df_stats[df_stats["Survecu"] == 1]
nb_survivantes = len(simulations_reussies)
temps_moyen = simulations_reussies["Temps_s"].mean() if nb_survivantes > 0 else 0

# Conversions pour la lisibilité du graphique
df["Année"] = df["Mois"] / 12
df["Population_Millions"] = df["Population"] / 1_000_000

# Extraction et calculs spécifiques pour la 15ème année (mois 180)
# Note : seules les simulations n'ayant pas crashé (count > 0) ont atteint ce mois
pop_an_15 = df[df["Mois"] == 180]["Population_Millions"]

if nb_survivantes > 0:
    moyenne = pop_an_15.mean()
    mediane = pop_an_15.median()
    ecart_type = pop_an_15.std()
    val_min = pop_an_15.min()
    val_max = pop_an_15.max()
    
    marge_erreur = 1.96 * (ecart_type / np.sqrt(nb_survivantes))
    ic_min = moyenne - marge_erreur
    ic_max = moyenne + marge_erreur
else:
    moyenne = mediane = ecart_type = val_min = val_max = ic_min = ic_max = 0

# Couleurs personnalisées
couleur_courbe = "#028090"  
couleur_texte = "#333333"   

# Génération de la courbe
ax = sns.lineplot(
    data=df,
    x="Année",
    y="Population_Millions",
    errorbar="sd",
    color=couleur_courbe,
    linewidth=1
)

# Personnalisation des titres et labels
plt.title("Évolution de la population de lapins sur 15 ans : un couple de lapins\n(Moyenne et écart-type sur 40 simulations)", 
          fontsize=14, fontweight='bold', pad=15, color=couleur_texte)
plt.xlabel("Temps (Années)", fontsize=12, fontweight='bold', color=couleur_texte)
plt.ylabel("Nombre de lapins (en millions)", fontsize=12, fontweight='bold', color=couleur_texte)

# Axe X et Y
ax.xaxis.set_major_locator(ticker.MultipleLocator(1))
ax.yaxis.set_major_formatter(ticker.FuncFormatter(lambda x, p: f"{int(x)}"))
ax.grid(True, linestyle='-', alpha=0.5)

# Construction de l'encart statistique enrichi
texte_stats = (
    f"Bilan Global (40 expériences) :\n"
    f"Simulations non éteintes : {nb_survivantes} / 40\n"
    f"Temps de calcul moyen : {temps_moyen:.2f} sec\n\n"
    f"Statistiques au bout de 15 ans (en millions) :\n"
    f"Moyenne : {moyenne:.1f} \n"
    f"Médiane : {mediane:.1f}\n"
    f"Écart-type (σ) : {ecart_type:.1f}\n"
    f"Plus petite population : {val_min:.1f}\n"
    f"Plus grande population : {val_max:.1f}\n"
    f"Int. Confiance (95%) : [{ic_min:.1f}, {ic_max:.1f}]"
)

# Ajout de l'encart sur le graphique (top left)
# La courbe exponentielle reste basse à gauche, l'encart ne la masquera pas
plt.text(0.02, 0.96, texte_stats, transform=ax.transAxes, fontsize=10,
         verticalalignment='top', color=couleur_texte, family='monospace',
         bbox=dict(boxstyle='round,pad=0.8', facecolor='white', alpha=0.9, edgecolor='#cccccc'))

plt.tight_layout()
plt.savefig("courbe_population_millions_stats.png", dpi=300, bbox_inches='tight')
print("Graphique sauvegardé sous : courbe_population_millions_stats.png")