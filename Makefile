all:
	@echo "Use 'make backuppackage' to generate a (non-bin-included)"
	@echo "tar.gz package, or 'make packages' to generate a distribution."

backuppackage:
	(cd src ; make clean)
	(cd .. ; tar -czv --exclude starana-0.2/bin -f sa-package.tar.gz starana-0.2/ )

packages: sourcepackage docpackage windllpackage binpackage

sourcepackage:
	(cd src ; make clean)
	(cd .. ; tar cvzf sa-src.tar.gz starana-0.2/src/ starana-0.2/xforms/ starana-0.2/perl/ starana-0.2/README starana-0.2/Makefile*)

docpackage:
	(cd .. ; zip -r9 sa-doc.zip starana-0.2/doc/* starana-0.2/examples/* starana-0.2/README)

windllpackage:
	(cd .. ; zip -r9 sa-windll.tar.gz starana-0.2/bin/*.dll starana-0.2/README)

binpackage:
#	(cd src ; $(MAKE))
#	mv src/starana bin/starana
#	mv src/starana.exe bin/starana.exe
#	(cd src ; $(MAKE) clean)
	(cd .. ; zip -r9 sa-bin.tar.gz starana-0.2/bin/starana* starana-0.2/README)
