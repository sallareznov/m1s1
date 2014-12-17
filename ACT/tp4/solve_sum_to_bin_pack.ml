open Certificat_bin_pack
open Probleme_sum_to_bin_pack

let usage () =
	Printf.printf "./solve_sum_to_bin_pack <fichier> : lit l'instance du probleme sum puis le reduit en ";
	Printf.printf "probleme de partitionnement\n"

let _ =
	if ((Array.length Sys.argv) < 2) then
		begin
			usage();
			exit(1)
		end
	else
		begin
			let fichier = Sys.argv.(1)
			in
			let probleme = construit_probleme_sum fichier
			in
			affiche_probleme_sum probleme;
	  		let solution = a_une_solution_sum_to_bin_pack probleme
	  		in
	  		if ((fst solution) = true) then
				begin
					let s1 = ref "" and donnees_certificat = (snd solution).donnees
					in
					for i = 0 to (Array.length donnees_certificat) - 2 do
						if (donnees_certificat.(i) = 0) then
							begin
								s1 := (!s1)^(string_of_int probleme.entiers_sum.(i));
								s1 := (!s1)^" + "
							end
					done;
					!s1.[(String.length !s1) - 2] <- '=';
					s1 := (!s1)^(string_of_int probleme.cible);
					Printf.printf "%s\n" (!s1)
				end
			else
				Printf.printf "Pas de solution\n";
	  		exit(0)
    	end
