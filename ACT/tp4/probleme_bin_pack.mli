exception Pas_de_certificat_suivant
type probleme_bin_pack = {
  nbre_objets : int;
  poids : int array;
  capacite_sacs : int;
  nbre_sacs : int;
}
val verifie_certificat :
  Certificat_bin_pack.certificat_bin_pack -> probleme_bin_pack -> bool
val affiche_probleme : probleme_bin_pack -> unit
val affiche_solution : Certificat_bin_pack.certificat_bin_pack -> unit
val a_une_solution_non_deterministe : probleme_bin_pack -> bool
val a_une_solution_deterministe :
  probleme_bin_pack -> bool * Certificat_bin_pack.certificat_bin_pack
val construit_probleme : string -> probleme_bin_pack
