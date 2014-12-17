type certificat_bin_pack = {
	donnees : int array
}

exception Pas_de_certificat_suivant

let affiche_donnees donnees =
  let s = ref "[|" and n = Array.length donnees
  in
    for i = 0 to Array.length donnees - 2 do
      s := (!s)^(string_of_int donnees.(i));
      s := (!s)^"; "
    done;
    s := (!s)^(string_of_int donnees.(n - 1));
    s := (!s)^"|]";
    Printf.printf "%s\n" (!s)

let genere_certificat_aleatoire n k =
  	let donnees = Array.make n 0
  	in
    Random.self_init();
    for i = 0 to n - 1 do
      donnees.(i) <- Random.int k
    done;
    { donnees = donnees }

let reset_certificat certificat =
	let donnees = certificat.donnees
	in
	for i = 0 to Array.length donnees - 1 do
		donnees.(i) <- 0
	done

let certificat_suivant certificat k =
	let donnees = certificat.donnees
	in
	let indice = ref (Array.length donnees - 1) and fait = ref false
	in
	while ((!indice >= 0) && (!fait = false)) do
		if (donnees.(!indice) < (k - 1)) then
	    	begin
	      		donnees.(!indice) <- donnees.(!indice) + 1;
         		fait := true;
	    	end
  		else
	    	begin
	      		donnees.(!indice) <- 0;
         		indice := !indice - 1;
	    	end
	done;
	if (!indice < 0) then
		begin
			reset_certificat certificat;
			raise Pas_de_certificat_suivant
		end
