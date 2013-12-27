import Criterion.Main
import Control.DeepSeq
import Queues

-- TEST CASES
-- General note: use the popped elements or they will be optimized away

-- n times popping an element and pushing another
test_pop_push :: (Queue, Integer) -> Integer
test_pop_push (q, 0) = 0
test_pop_push (q, n) =
	let (x, q') = generic_q_pop q in
	x + test_pop_push(generic_q_push n q', n-1)

-- pop n elements off the queue
test_pop :: (Queue, Integer) -> Integer
test_pop (q, 0) = 0
test_pop (q, n) =
	let (x, q') = generic_q_pop q in
	x + test_pop(q', n-1)

-- push n elements onto the queue
test_push :: (Queue, Integer) -> Integer
test_push (q, 0) = let (x, _) = generic_q_pop q in x
test_push (q, n) =
	test_push(generic_q_push n q, n-1)


-- repeatedly push some element to the same queue, 
-- popping an element as well to make it not be optimized away
test_repeated_push_pop :: (Queue, Integer) -> [Integer]
test_repeated_push_pop (q, n) = 
	[ let (x,_) = generic_q_pop (generic_q_push i q) in x | i <- [1..n] ]




-- TEST DATA
make_test_queue :: (Queue, Integer) -> Queue
make_test_queue (q, 0) = q
make_test_queue (q, n) = 
	make_test_queue (generic_q_push n q, n-1)

listQ = make_test_queue (generic_q_make TList, 10000)
strictQ = make_test_queue (generic_q_make TStrict, 10000)
lazyQ = make_test_queue (generic_q_make TLazy, 10000)
realtimeQ = make_test_queue (generic_q_make TRealTime, 10000)


-- less repeated code
make_whnf_test_group :: (String, (Queue, Integer) -> Integer) -> Benchmark
make_whnf_test_group (s, f) =
	bgroup s
		[ bench "list" $ whnf f (listQ, 1000)
		, bench "strict" $ whnf f (strictQ, 1000)
		, bench "lazy" $ whnf f (lazyQ, 1000)
		, bench "realtime" $ whnf f (realtimeQ, 1000)
		]

make_nf_test_group :: (String, (Queue, Integer) -> [Integer]) -> Benchmark
make_nf_test_group (s, f) =
	bgroup s
		[ bench "list" $ nf f (listQ, 1000)
		, bench "strict" $ nf f (strictQ, 1000)
		, bench "lazy" $ nf f (lazyQ, 1000)
		, bench "realtime" $ nf f (realtimeQ, 1000)
		]


-- RUNNING TESTS
main = defaultMain [
	make_whnf_test_group ("test_pop_push", test_pop_push),
	make_whnf_test_group ("test_pop", test_pop),
	make_whnf_test_group ("test_push", test_push),
	make_nf_test_group ("test_repeated_push_pop", test_repeated_push_pop)



	--bgroup "test_pop_push"
	--	[ bench "list" $ whnf test_pop_push (listQ, 1000)
	--	, bench "strict" $ whnf test_pop_push (strictQ, 1000)
	--	, bench "lazy" $ whnf test_pop_push (lazyQ, 1000)
	--	, bench "realtime" $ whnf test_pop_push (realtimeQ, 1000)
	--	],
	--bgroup "test_pop"
	--	[ bench "list" $ whnf test_pop (listQ, 1000)
	--	, bench "strict" $ whnf test_pop (strictQ, 1000)
	--	, bench "lazy" $ whnf test_pop (lazyQ, 1000)
	--	, bench "realtime" $ whnf test_pop (realtimeQ, 1000)
	--	],
 --  bgroup "test_push"
 --  	[ bench "list" $ whnf test_push (listQ, 1000)
	--	, bench "strict" $ whnf test_push (strictQ, 1000)
	--	, bench "lazy" $ whnf test_push (lazyQ, 1000)
	--	, bench "realtime" $ whnf test_push (realtimeQ, 1000)
	--	],
	--bgroup "test_repeated_push_pop"
 --  	[ bench "list" $ nf test_repeated_push_pop (listQ, 1000)
	--	, bench "strict" $ nf test_repeated_push_pop (strictQ, 1000)
	--	, bench "lazy" $ nf test_repeated_push_pop (lazyQ, 1000)
	--	, bench "realtime" $ nf test_repeated_push_pop (realtimeQ, 1000)
	--	]
   ]
