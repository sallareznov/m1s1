open Certificat_bin_pack

exception Pas_de_certificat_suivant

type probleme_bin_pack = {
  nbre_objets : int;
  poids : int array;
  capacite_sacs : int;
  nbre_sacs : int;
}

let verifie_certificat certificat probleme =
  let est_valide = ref true and capacites_sacs = Array.make probleme.capacite_sacs 0 and i = ref 0
  in
    while ((!i < probleme.nbre_objets) && (!est_valide = true)) do
      let num_sac = certificat.donnees.(!i)
        in
        capacites_sacs.(num_sac) <- capacites_sacs.(num_sac) + probleme.poids.(!i);
        if (capacites_sacs.(num_sac) > probleme.capacite_sacs) then begin
            est_valide := false
        end;
        i := !i + 1;
    done;
    !est_valide

let affiche_probleme probleme =
	Printf.printf "%s\n" (String.make 50 '-');
	Printf.printf "Probleme :\n";
  	Printf.printf "nbre_objets = %d\n" probleme.nbre_objets;
  	Printf.printf "poids = ";
  	affiche_donnees probleme.poids;
  	Printf.printf "capacites_sacs = %d\n" probleme.capacite_sacs;
  	Printf.printf "nbre_sacs = %d\n" probleme.nbre_sacs;
	Printf.printf "%s\n" (String.make 50 '-')

let affiche_solution certificat =
	let donnees = certificat.donnees
	in
	for i = 0 to Array.length donnees - 1 do
		Printf.printf "objet %d -> sac %d\n" i donnees.(i)
	done

let a_une_solution_non_deterministe probleme =
  let certificat = genere_certificat_aleatoire probleme.nbre_objets probleme.nbre_sacs and trouve = ref false
  in
    Printf.printf "certificat aleatoire genere = ";
    affiche_donnees certificat.donnees;
    trouve := verifie_certificat certificat probleme;
    !trouve

let a_une_solution_deterministe probleme =
  let n = probleme.nbre_objets and k = probleme.nbre_sacs
  in
  let donnees = Array.make n 0
  in
  let certificat = { donnees = donnees }
  in
  let trouve = ref false
  in
    try
      while (!trouve = false) do
        certificat_suivant certificat k;
        trouve := verifie_certificat certificat probleme
      done;
      (!trouve, certificat)
    with
      | Certificat_bin_pack.Pas_de_certificat_suivant -> (!trouve, certificat)

let construit_probleme fichier =
  let entree = open_in fichier
  in
  let n = (int_of_string (input_line entree))
  in
  let p = Array.make n 0
  in
    for i = 0 to n - 1 do
      p.(i) <- (int_of_string (input_line entree))
    done;
    let k = (int_of_string (input_line entree)) and c = (int_of_string (input_line entree))
    in
    close_in entree;
    { nbre_objets = n ; poids = p ; capacite_sacs = c ; nbre_sacs = k }
