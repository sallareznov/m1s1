type certificat_bin_pack = { donnees : int array; }
exception Pas_de_certificat_suivant
val affiche_donnees : int array -> unit
val genere_certificat_aleatoire : int -> int -> certificat_bin_pack
val reset_certificat : certificat_bin_pack -> unit
val certificat_suivant : certificat_bin_pack -> int -> unit
