pdflatex -file-line-error -interaction=nonstopmode -synctex=1 -output-format=pdf Paper.tex
biber Paper
pdflatex -file-line-error -interaction=nonstopmode -synctex=1 -output-format=pdf Paper.tex