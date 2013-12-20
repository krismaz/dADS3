 import Criterion.Main

 fib :: Int -> Int
 fib 0 = 0
 fib 1 = 1
 fib n = fib (n-1) + fib (n-2)

 main = defaultMain [
        bgroup "fib" [ bench "10" $ whnf fib 10
                     , bench "15" $ whnf fib 15
                     , bench "20" $ whnf fib 20
                     ]
                    ]