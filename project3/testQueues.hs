import Criterion.Main
import Control.DeepSeq
import Queues

-- TEST CASES
-- General note: use the popped elements or they will be optimized away

-- n times popping an element and injecting another
test_pop_inject :: (Queue, Int) -> [Int]
test_pop_inject (q, 0) = []
test_pop_inject (q, n) =
	let (x, q') = generic_q_pop q in
	x : test_pop_inject(generic_q_inject n q', n-1)

-- pop n elements off the queue
test_pop :: (Queue, Int) -> [Int]
test_pop (q, 0) = []
test_pop (q, n) =
	let (x, q') = generic_q_pop q in
	x : test_pop(q', n-1)

-- inject n elements onto the queue
test_inject :: (Queue, Int) -> [Int]
test_inject (q, 0) = let (x, _) = generic_q_pop q in [x]
test_inject (q, n) = test_inject(generic_q_inject n q, n-1)


-- repeatedly inject some element to the same queue, 
-- popping an element as well to make it not be optimized away
test_repeated_inject_pop :: (Queue, Int) -> [Int]
test_repeated_inject_pop (q, n) = 
	[ let (x,_) = generic_q_pop (generic_q_inject i q) in x | i <- [1..n] ]




-- TEST DATA
make_test_queue :: (Queue, Int) -> Queue
make_test_queue (q, 0) = q
make_test_queue (q, n) = 
	make_test_queue (generic_q_inject n q, n-1)


-- less repeated code
make_nf_test_group :: (String, (Queue, Int) -> [Int], Int) -> Benchmark
make_nf_test_group (s, f, n) =
	let listQ = make_test_queue (generic_q_make TList, n) in
	let strictQ = make_test_queue (generic_q_make TStrict, n) in
	let lazyQ = make_test_queue (generic_q_make TLazy, n) in
	let realtimeQ = make_test_queue (generic_q_make TRealTime, n) in
	bgroup s
		[ bench "list" $ nf f (listQ, 500)
		, bench "strict" $ nf f (strictQ, 500)
		, bench "lazy" $ nf f (lazyQ, 500)
		, bench "realtime" $ nf f (realtimeQ, 500)
		]

make_sized_array_test_group :: Int -> Benchmark
make_sized_array_test_group n = 
	bgroup (show n)
		[ make_nf_test_group ("test_pop_inject", test_pop_inject, n)
		, make_nf_test_group ("test_pop", test_pop, n)
		, make_nf_test_group ("test_inject", test_inject, n)
		, make_nf_test_group ("test_repeated_inject_pop", test_repeated_inject_pop, n)
		]



-- RUNNING TESTS
main = defaultMain [
	make_sized_array_test_group 500,
	make_sized_array_test_group 1000,
	make_sized_array_test_group 1500,
	make_sized_array_test_group 2000,
	make_sized_array_test_group 2500,
	make_sized_array_test_group 3000,
	make_sized_array_test_group 3500,
	make_sized_array_test_group 4000,
	make_sized_array_test_group 4500,
	make_sized_array_test_group 5000,
	make_sized_array_test_group 5500,
	make_sized_array_test_group 6000,
	make_sized_array_test_group 6500,
	make_sized_array_test_group 7000,
	make_sized_array_test_group 7500,
	make_sized_array_test_group 8000,
	make_sized_array_test_group 8500,
	make_sized_array_test_group 9000,
	make_sized_array_test_group 9500,
	make_sized_array_test_group 10000
   ]
