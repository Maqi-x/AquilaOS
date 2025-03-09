#!/bin/bash
cd "$(dirname "$0")" || exit
set -e
source ./utils.sh
cd ..

totalLinesTOTAL=0

infoOf() {
  ext="$1"
  files=()

  while IFS= read -r -d '' file; do
      files+=("$file")
  done < <(find . -type f -name "*$ext" -print0)
  fileCount=${#files[@]}

  if [[ $fileCount -eq 0 ]]; then
    printf "\033[1;33m[ INFO ]: No files found with extension %s\033[0m\n" "$ext"
    return
  fi
  local totalLines=0

  for file in "${files[@]}"; do
    totalLines=$((totalLines + $(wc -l < "$file")))
    totalLinesTOTAL=$((totalLinesTOTAL + $(wc -l < "$file")))
  done

  # printf "$color[ ANALYSIS ]:\033[0m Files with extension \033[1;34m%s\033[0m\n" "$ext"
case "$ext" in
    ".py")
        printf "\033[1;32m[ ANALYSIS ]: \033[1;34mPython\033[0m source files\n";;
    ".go")
        printf "\033[1;32m[ ANALYSIS ]: \033[1;34mGo\033[0m source files\n";;
    ".cpp")
        printf "\033[1;32m[ ANALYSIS ]: \033[1;34mC++\033[0m source files\n";;
    ".asm")
        printf "\033[1;32m[ ANALYSIS ]: \033[1;34mAssembler\033[0m source files\n";;
    ".sh")
        printf "\033[1;32m[ ANALYSIS ]: \033[1;34mShell script\033[0m files\n";;
    ".hpp")
        printf "\033[1;32m[ ANALYSIS ]: \033[1;34m C++\033[0m headers\n";;   
    *)
        printf "\033[1;32m[ ANALYSIS ]: \033[0mFiles with extension \033[1;34m%s\033[0m\n" "$ext";;
esac

  printf "  \033[1;36m» Total number of files:\033[0m %d\n" "$fileCount"
  printf "  \033[1;36m» Total number of lines:\033[0m %d\n" "$totalLines"
  if [[ "$ext" = ".go" ]]; then
    printf "  \033[1;36m» Total go modules:\033[0m %d\n" "$(find . -type f -name "go.mod" | wc -l)"
  fi
}


clear
printf "\033[1;34m[ DIRECTORY ANALYSIS ]: \033[0m\033[1;36m%s\033[0m\n" "$(pwd)"
Sep

# ------------------------------------------------------------------------------ #

# infoOf ".py" "\033[1;32m"
# Sep
# infoOf ".go" "\033[1;32m"
# Sep
# infoOf ".s" "\033[1;32m"
# Sep
infoOf ".cpp"
Sep
infoOf ".hpp"
Sep
infoOf ".asm"
Sep
infoOf ".sh"
Sep

# ------------------------------------------------------------------------------ #
printf "\033[1;34m[ TOTAL ]: \033[0m\n"

# ---- Shit, not working ----- #
#totalLines1=$(( $(find . -type f -name "*.py" -print0 | xargs -0 wc -l | awk '{total += $1} END {print total}') + $(find . -type f -name "*.go" -print0 | xargs -0 wc -l | awk '{total += $1} END {print total}') + $(find . -type f -name "*.sh" -print0 | xargs -0 wc -l | awk '{total += $1} END {print total}') ))

totalFiles1=$(( $(find . -type f -name "*.py" -print0 | xargs -0 -I {} echo {} | wc -l) + $(find . -type f -name "*.go" -print0 | xargs -0 -I {} echo {} | wc -l) + $(find . -type f -name "*.sh" -print0 | xargs -0 -I {} echo {} | wc -l) ))
#totalLines1="$(python -c "import glob; x = lambda y: sum(sum(1 for _ in open(f)) for f in glob.glob(f\"**/*.{y}\", recursive=True)); print(x(\"go\") + x(\"py\") + x(\"sh\"))")" # I'm a idiot, but it's working btw
printf "  \033[1;36m» Number of files:\033[0m %d\n" "$totalFiles1"
printf "  \033[1;36m» Number of lines:\033[0m %d\n" "$totalLinesTOTAL"
Sep