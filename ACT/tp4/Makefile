#### COMPILATORS ####

COPT	= ocamlc.opt
OPTOPT	= ocamlopt.opt

#### FILES TO CLEAN ####

MLIS 		= certificat_bin_pack.mli probleme_bin_pack.mli probleme_partition_to_bin_pack_to_bin_pack.mli
CMIS		= certificat_bin_pack.cmi probleme_bin_pack.cmi probleme_partition_to_bin_pack.cmi probleme_sum_to_partition.cmi solve_bin_pack.cmi solve_partition_to_bin_pack.cmi solve_sum_to_partition.cmi
CMXS		= certificat_bin_pack.cmx probleme_bin_pack.cmx probleme_partition_to_bin_pack.cmx probleme_sum_to_partition.cmx solve_bin_pack.cmx solve_partition_to_bin_pack.cmx solve_sum_to_partition.cmx
BINARIES	= solve_bin_pack solve_partition_to_bin_pack solve_sum_to_partition

#### RULES TO CALL AT THE COMPILATION ####

CERTIFICAT_BIN_PACK 			= certificat_bin_pack.mli certificat_bin_pack.cmi certificat_bin_pack.cmx
PROBLEME_BIN_PACK 				= probleme_bin_pack.mli probleme_bin_pack.cmi probleme_bin_pack.cmx
PROBLEME_PARTITION_TO_BIN_PACK 	= probleme_partition_to_bin_pack.mli probleme_partition_to_bin_pack.cmi probleme_partition_to_bin_pack.cmx
PROBLEME_SUM_TO_PARTITION 		= probleme_sum_to_partition.mli probleme_sum_to_partition.cmi probleme_sum_to_partition.cmx
SOLVE 							= solve_bin_pack.cmx solve_bin_pack solve_partition_to_bin_pack.cmx solve_partition_to_bin_pack solve_sum_to_partition.cmx solve_sum_to_partition

EXEC	= $(CERTIFICAT_BIN_PACK) $(PROBLEME_BIN_PACK) $(PROBLEME_PARTITION_TO_BIN_PACK) $(PROBLEME_SUM_TO_PARTITION) $(SOLVE)

all: $(EXEC)

#### MLIS ####

certificat_bin_pack.mli:
	$(COPT) -i certificat_bin_pack.ml > certificat_bin_pack.mli

probleme_bin_pack.mli:
	$(COPT) -i probleme_bin_pack.ml > probleme_bin_pack.mli

probleme_partition_to_bin_pack.mli:
	$(COPT) -i probleme_partition_to_bin_pack.ml > probleme_partition_to_bin_pack.mli

probleme_sum_to_partition.mli:
	$(COPT) -i probleme_sum_to_partition.ml > probleme_sum_to_partition.mli

probleme_sum_to_bin_pack.mli:
	$(COPT) -i probleme_sum_to_bin_pack.ml > probleme_sum_to_bin_pack.mli

#### CMIS ####

certificat_bin_pack.cmi: certificat_bin_pack.mli
	$(COPT) -c certificat_bin_pack.mli -o certificat_bin_pack.cmi

probleme_bin_pack.cmi: certificat_bin_pack.cmi probleme_bin_pack.mli
	$(COPT) -c probleme_bin_pack.mli -o probleme_bin_pack.cmi

probleme_partition_to_bin_pack.cmi: probleme_bin_pack.cmi probleme_partition_to_bin_pack.mli
	$(COPT) -c probleme_partition_to_bin_pack.mli -o probleme_partition_to_bin_pack.cmi

probleme_sum_to_partition.cmi: probleme_partition_to_bin_pack.cmi probleme_sum_to_partition.mli
	$(COPT) -c probleme_sum_to_partition.mli -o probleme_sum_to_partition.cmi

probleme_sum_to_bin_pack.cmi: probleme_sum_to_partition.cmi probleme_partition_to_bin_pack.cmi probleme_sum_to_bin_pack.mli
	$(COPT) -c probleme_sum_to_bin_pack.mli -o probleme_sum_to_bin_pack.cmi

#### CMXS ####

certificat_bin_pack.cmx: certificat_bin_pack.ml
	$(OPTOPT) -c certificat_bin_pack.ml -o certificat_bin_pack.cmx

probleme_bin_pack.cmx: certificat_bin_pack.cmx probleme_bin_pack.ml
	$(OPTOPT) -c probleme_bin_pack.ml -o probleme_bin_pack.cmx

probleme_partition_to_bin_pack.cmx: probleme_bin_pack.cmx probleme_partition_to_bin_pack.ml
	$(OPTOPT) -c probleme_partition_to_bin_pack.ml -o probleme_partition_to_bin_pack.cmx

probleme_sum_to_partition.cmx: probleme_partition_to_bin_pack.cmx probleme_sum_to_partition.ml
	$(OPTOPT) -c probleme_sum_to_partition.ml -o probleme_sum_to_partition.cmx

probleme_sum_to_bin_pack.cmx: probleme_sum_to_partition.cmx probleme_sum_to_bin_pack.cmx probleme_sum_to_bin_pack.ml
	$(OPTOPT) -c probleme_sum_to_bin_pack.ml -o probleme_sum_to_bin_pack.cmx

solve_bin_pack.cmx: certificat_bin_pack.cmx probleme_bin_pack.cmx solve_bin_pack.ml
	$(OPTOPT) -c solve_bin_pack.ml -o solve_bin_pack.cmx

solve_partition_to_bin_pack.cmx: probleme_partition_to_bin_pack.cmx solve_partition_to_bin_pack.ml
	$(OPTOPT) -c solve_partition_to_bin_pack.ml -o solve_partition_to_bin_pack.cmx

solve_sum_to_partition.cmx: probleme_sum_to_partition.cmx solve_sum_to_partition.ml
	$(OPTOPT) -c solve_sum_to_partition.ml -o solve_sum_to_partition.cmx

solve_sum_to_bin_pack.cmx: probleme_sum_to_bin_pack.cmx solve_sum_to_bin_pack.ml
	$(OPTOPT) -c solve_sum_to_bin_pack.ml -o solve_sum_to_bin_pack.cmx

#### BINARIES ####

solve_bin_pack: solve_bin_pack.cmx
	$(OPTOPT) certificat_bin_pack.cmx probleme_bin_pack.cmx solve_bin_pack.cmx -o solve_bin_pack

solve_partition_to_bin_pack: solve_partition_to_bin_pack.cmx
	$(OPTOPT) certificat_bin_pack.cmx probleme_bin_pack.cmx probleme_partition_to_bin_pack.cmx solve_partition_to_bin_pack.cmx -o solve_partition_to_bin_pack

solve_sum_to_partition: solve_sum_to_partition.cmx
	$(OPTOPT) certificat_bin_pack.cmx probleme_bin_pack.cmx probleme_partition_to_bin_pack.cmx probleme_sum_to_partition.cmx solve_sum_to_partition.cmx -o solve_sum_to_partition

solve_sum_to_bin_pack: probleme_sum_to_bin_pack.cmx solve_sum_to_partition.cmx
	$(OPTOPT) certificat_bin_pack.cmx probleme_bin_pack.cmx probleme_partition_to_bin_pack.cmx probleme_sum_to_partition.cmx solve_sum_to_bin_pack.cmx -o solve_sum_to_bin_pack

#### CLEAN ####

.PHONY: $(MLIS) probleme_sum_to_partition.mli clean mrproper

clean:
	$(RM) -rf $(CMIS) *.cmo $(CMXS) *.o

mrproper:
	$(RM) -rf $(BINARIES) *~

realclean: clean mrproper
