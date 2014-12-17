type probleme_partition = {
  nbre_entiers_partition : int;
  entiers_partition : int array;
}
val somme_entiers_probleme_partition : probleme_partition -> int
val affiche_probleme_partition : probleme_partition -> unit
val red_poly_partition :
  probleme_partition -> Probleme_bin_pack.probleme_bin_pack
val a_une_solution_partition :
  probleme_partition -> bool * Certificat_bin_pack.certificat_bin_pack
val construit_probleme_partition : string -> probleme_partition
