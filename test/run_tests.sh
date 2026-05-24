#!/bin/bash

TPCC="$(dirname "$0")/../bin/tpcc"
TESTDIR="$(dirname "$0")"

run_suite() {
    local dir="$1"
    local expected="$2"
    local label="$3"
    local ok=0
    local total=0

    echo "=== $label (code attendu : $expected) ==="
    for f in "$dir"/*.tpc; do
        [ -f "$f" ] || continue
        "$TPCC" < "$f" >/dev/null 2>&1
        code=$?
        total=$((total + 1))
        if [ "$code" -eq "$expected" ]; then
            ok=$((ok + 1))
            echo "  OK  $(basename "$f")"
        else
            echo "  FAIL $(basename "$f")  (obtenu: $code)"
        fi
    done
    echo "  Score : $ok / $total"
    echo ""
    SUITE_OK=$ok
    SUITE_TOTAL=$total
}

ok_good=0;  tot_good=0
ok_syn=0;   tot_syn=0
ok_sem=0;   tot_sem=0
ok_warn=0;  tot_warn=0

run_suite "$TESTDIR/good"    0 "Programmes corrects (good)"
ok_good=$SUITE_OK; tot_good=$SUITE_TOTAL

run_suite "$TESTDIR/syn-err" 1 "Erreurs lexicales/syntaxiques (syn-err)"
ok_syn=$SUITE_OK; tot_syn=$SUITE_TOTAL

run_suite "$TESTDIR/sem-err" 2 "Erreurs sémantiques (sem-err)"
ok_sem=$SUITE_OK; tot_sem=$SUITE_TOTAL

run_suite "$TESTDIR/warn"    0 "Avertissements (warn)"
ok_warn=$SUITE_OK; tot_warn=$SUITE_TOTAL

total_ok=$((ok_good + ok_syn + ok_sem + ok_warn))
total_all=$((tot_good + tot_syn + tot_sem + tot_warn))

echo "========================================="
echo " RAPPORT FINAL"
echo "========================================="
printf "  good    : %s / %s\n" "$ok_good"  "$tot_good"
printf "  syn-err : %s / %s\n" "$ok_syn"   "$tot_syn"
printf "  sem-err : %s / %s\n" "$ok_sem"   "$tot_sem"
printf "  warn    : %s / %s\n" "$ok_warn"  "$tot_warn"
echo "-----------------------------------------"
printf "  TOTAL   : %s / %s\n" "$total_ok" "$total_all"
echo "========================================="
