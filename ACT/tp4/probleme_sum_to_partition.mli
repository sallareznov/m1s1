type probleme_sum = {
  nbre_entiers_sum : int;
  entiers_sum : int array;
  cible : int;
}
val somme_entiers_probleme_sum : probleme_sum -> int
val affiche_probleme_sum : probleme_sum -> unit
val red_poly_sum_to_partition :
  probleme_sum -> Probleme_partition_to_bin_pack.probleme_partition
val a_une_solution_sum_to_partition :
  probleme_sum -> bool * Certificat_bin_pack.certificat_bin_pack
val construit_probleme_sum : string -> probleme_sum
