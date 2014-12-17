open Certificat_bin_pack
open Probleme_partition_to_bin_pack

let usage () =
	Printf.printf "./solve_partition_to_bin_pack <fichier> : lit l'instance du probleme de partitionnement puis le reduit en ";
	Printf.printf "probleme de bin-packing avec 2 sacs et affiche un certificat si la somme des entiers du sac 0 est egale à celle des ";
	Printf.printf "entiers du sac 1.\n"

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
			let probleme = construit_probleme_partition fichier
			in
			affiche_probleme_partition probleme;
	  		let solution = a_une_solution_partition probleme
	  		in
	  		if ((fst solution) = true) then
				begin
					let s1 = ref "" and s2 = ref "" and donnees_certificat = (snd solution).donnees
					in
					for i = 0 to (Array.length donnees_certificat) - 1 do
						if (donnees_certificat.(i) = 0) then
							begin
								s1 := (!s1)^(string_of_int probleme.entiers_partition.(i));
								s1 := (!s1)^" + "
							end
						else
							begin
								s2 := (!s2)^(string_of_int probleme.entiers_partition.(i));
								s2 := (!s2)^" + "
							end
					done;
					!s1.[(String.length !s1) - 2] <- '=';
					!s2.[(String.length !s2) - 2] <- '=';
					s1 := (!s1)^(string_of_int ((somme_entiers_probleme_partition probleme) / 2));
					s2 := (!s2)^(string_of_int ((somme_entiers_probleme_partition probleme) / 2));
					Printf.printf "Une solution trouvee :\n";
					Printf.printf "%s\n%s\n" (!s1) (!s2)
				end
			else
				Printf.printf "Pas de solution\n";
	  		exit(0)
    	end
