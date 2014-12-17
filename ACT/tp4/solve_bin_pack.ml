open Certificat_bin_pack
open Probleme_bin_pack

let usage () =
  Printf.printf "./solve_bin_pack <fichier> (-v | -nd | -exh) : lit l'instance du probleme de bin-packing dans fichier et recherche un certificat ";
  Printf.printf "par le ou les modes choisis. Une solution est affichee, s'il en existe.\n";
  Printf.printf "-v = mode verification : l'utilisateur entre un certificat, et le programme verifie que c'est une solution au probleme\n";
  Printf.printf "-nd = mode non deterministe : un certificat aleatoire est generee et passe au programme\n";
  Printf.printf "-exh = mode exhaustif : tous les certificats possibles sont passes au programme. Le premier qui satisfait le probleme est affiche\n"

let solve_mode_non_deterministe probleme =
	Printf.printf "####### MODE NON DETERMINISTE #######\n";
	affiche_probleme probleme;
	if ((a_une_solution_non_deterministe probleme) = true) then
  		Printf.printf "Le certificat genere est une solution\n"
	else
		Printf.printf "Le certificat genere n'est pas une solution\n"

let solve_mode_exhaustif probleme =
	Printf.printf "####### MODE EXHAUSTIF #######\n";
	affiche_probleme probleme;
	let solution = a_une_solution_deterministe probleme
	in
  	if ((fst solution) = true) then
  		begin
  			Printf.printf "Une solution trouvee :\n";
  			affiche_solution (snd solution)
  		end
 	else
    	Printf.printf "Pas de solution\n"

let a_une_solution_par_verification probleme certificat =
	let trouve = ref false
	in
	trouve := verifie_certificat certificat probleme;
	!trouve

let solve_mode_verif probleme =
  let donnees = Array.make probleme.nbre_objets 0 and i = ref 0 and valide = ref true
  in
    Printf.printf "####### MODE VERIFICATION ########\n";
    affiche_probleme probleme;
    Printf.printf "certificat =\n";
    while ((!i < Array.length probleme.poids) && (!valide = true)) do
      Printf.printf "%d -> " !i;
      let valeur = read_int()
      in
        if (valeur >= probleme.nbre_sacs) then
          valide := false;
        donnees.(!i) <- valeur;
                      i := !i + 1
    done;
    if (!valide = false) then
      Printf.printf "Numeros de sac du certificat incorrects\n"
    else
      let certificat = { donnees = donnees }
      in
      if ((a_une_solution_par_verification probleme certificat) = true) then
       	Printf.printf "Le certificat saisi est une solution\n"
    else
      Printf.printf "Le certificat saisi n'est pas une solution\n"

let _ =
  if ((Array.length Sys.argv) < 3) then
    begin
      usage();
      exit(1)
    end
  else
    begin
      let fichier = Sys.argv.(1)
      in
      let probleme = construit_probleme fichier
      in
        for i = 2 to Array.length Sys.argv - 1 do
          match Sys.argv.(i) with
            | "-nd" ->
            begin
              solve_mode_non_deterministe probleme
            end
            | "-exh" ->
              begin
                solve_mode_exhaustif probleme
              end
            | "-v" ->
              begin
                solve_mode_verif probleme
              end
            | input ->
              begin
                Printf.printf "Mode inconnu : %s\n" input;
              end
        done;
        exit(0)
    end