open Certificat_bin_pack
open Probleme_bin_pack

type probleme_partition = {
    nbre_entiers_partition : int;
    entiers_partition : int array;
}

let somme_entiers_probleme_partition probleme =
	let entiers_partition_probleme = probleme.entiers_partition and cpt = ref 0
	in
	for i = 0 to Array.length entiers_partition_probleme - 1 do
		cpt := !cpt + entiers_partition_probleme.(i)
	done;
	!cpt

let affiche_probleme_partition probleme =
	Printf.printf "%s\n" (String.make 50 '-');
	Printf.printf "Probleme :\n";
	Printf.printf "nbre_entiers_partition = %d\n" probleme.nbre_entiers_partition;
	Printf.printf "entiers_partition = ";
	affiche_donnees probleme.entiers_partition;
	Printf.printf "somme entiers_partition = %d\n" (somme_entiers_probleme_partition probleme);
	Printf.printf "%s\n" (String.make 50 '-')

let red_poly_partition prob_partition =
	let n = prob_partition.nbre_entiers_partition and p = prob_partition.entiers_partition
	and c = ((somme_entiers_probleme_partition prob_partition) / 2) and k = 2
	in
	{ nbre_objets = n ; poids = p ; capacite_sacs = c ; nbre_sacs = k }

let a_une_solution_partition prob_partition =
	if ((somme_entiers_probleme_partition prob_partition) mod 2 = 1) then
		begin
			Printf.printf "La somme des entiers_partition est impaire => pas de solution\n";
			exit(1)
		end
	else
		let prob_bin_pack = red_poly_partition prob_partition
		in
		a_une_solution_deterministe prob_bin_pack

let construit_probleme_partition fichier =
  let entree = open_in fichier
  in
  let n = (int_of_string (input_line entree))
  in
  let e = Array.make n 0
  in
    for i = 0 to n - 1 do
      e.(i) <- (int_of_string (input_line entree))
    done;
    close_in entree;
    { nbre_entiers_partition = n ; entiers_partition = e }
