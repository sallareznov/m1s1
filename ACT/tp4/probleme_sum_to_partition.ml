open Certificat_bin_pack
open Probleme_partition_to_bin_pack

type probleme_sum = {
	nbre_entiers_sum : int;
	entiers_sum : int array;
	cible : int
}

let somme_entiers_probleme_sum probleme =
	let entiers_probleme = probleme.entiers_sum and cpt = ref 0
	in
	for i = 0 to Array.length entiers_probleme - 1 do
		cpt := !cpt + entiers_probleme.(i)
	done;
	!cpt

let affiche_probleme_sum probleme =
	Printf.printf "%s\n" (String.make 50 '-');
	Printf.printf "Probleme :\n";
	Printf.printf "nbre_entiers = %d\n" probleme.nbre_entiers_sum;
	Printf.printf "entiers = ";
	affiche_donnees probleme.entiers_sum;
	Printf.printf "cible = %d\n" probleme.cible;
	Printf.printf "%s\n" (String.make 50 '-')

let red_poly_sum_to_partition prob_sum =
	let n_prob_sum = Array.length prob_sum.entiers_sum
	in
	let n_prob_partition = n_prob_sum + 1
	in
  	let entiers_partition = Array.make n_prob_partition 0
	in
	for i = 0 to n_prob_sum - 1 do
		entiers_partition.(i) <- prob_sum.entiers_sum.(i)
  	done;
	entiers_partition.(n_prob_partition - 1) <- abs((2 * prob_sum.cible) - (somme_entiers_probleme_sum prob_sum));
	let n = prob_sum.nbre_entiers_sum + 1
	in
	{ nbre_entiers_partition = n ; entiers_partition = entiers_partition }

let a_une_solution_sum_to_partition prob_sum =
	let prob_partition = red_poly_sum_to_partition prob_sum
	in
	a_une_solution_partition prob_partition

let construit_probleme_sum fichier =
	let entree = open_in fichier
	in
	let n = (int_of_string (input_line entree))
	in
	let e = Array.make n 0
	in
	for i = 0 to n - 1 do
		e.(i) <- (int_of_string (input_line entree))
	done;
	let c = (int_of_string (input_line entree))
	in
    close_in entree;
    { nbre_entiers_sum = n ; entiers_sum = e ; cible = c }
