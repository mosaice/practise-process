findit () {
  if test $# -eq 1; then
    findit $1 .
  else
    if test -d $2; then
      grep -snH $1 $2/*.c $2/*.h 
      (cd $2
      for j in *; do
        if test -d $j; then
          findit $1 $j
        fi
      done
      )
    fi  
  fi
}

findit $1 $2
