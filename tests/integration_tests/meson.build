tests = [
#            'env-ctmrg-rvb-2x2',
#            'env-ctmrg-rvb-1x2',
            'env-ctmrg-aklt-2x2',
            'opt-su-hb-1x2',
            'opt-fu-hb-1x2'
]

compare = find_program('compare.sh')
compare_ll = find_program('compare-last-line.sh')
find_program('numdiff', required:true)

foreach _test : tests
    subdir(_test) # build the test
endforeach
