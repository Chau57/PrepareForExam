shopt -s nullglob

for f in *\ [0-9]*.docx; do
    n=${f##* }
    n=${n%.docx}

    mkdir -p "exe_$n"
    mv "$f" "exe_$n/problem_$n.docx"
    touch "exe_$n/solve_$n.cpp"
done