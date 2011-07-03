import IO

main =
    do
        a <- readLn
        if a == 42 then return ()
            else
                do
                    print a
                    main
