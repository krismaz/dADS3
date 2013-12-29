import Criterion.Main
import Control.DeepSeq
import Queues

-- TEST CASES
-- General note: use the popped elements or they will be optimized away

-- n times popping an element and pushing another
test_pop_push :: (Queue, Int) -> [Int]
test_pop_push (q, 0) = []
test_pop_push (q, n) =
	let (x, q') = generic_q_pop q in
	x : test_pop_push(generic_q_push n q', n-1)

-- pop n elements off the queue
test_pop :: (Queue, Int) -> [Int]
test_pop (q, 0) = []
test_pop (q, n) =
	let (x, q') = generic_q_pop q in
	x : test_pop(q', n-1)

-- push n elements onto the queue
test_push :: (Queue, Int) -> [Int]
test_push (q, 0) = let (x, _) = generic_q_pop q in [x]
test_push (q, n) = test_push(generic_q_push n q, n-1)


-- repeatedly push some element to the same queue, 
-- popping an element as well to make it not be optimized away
test_repeated_push_pop :: (Queue, Int) -> [Int]
test_repeated_push_pop (q, n) = 
	[ let (x,_) = generic_q_pop (generic_q_push i q) in x | i <- [1..n] ]




-- TEST DATA
make_test_queue :: (Queue, Int) -> Queue
make_test_queue (q, 0) = q
make_test_queue (q, n) = 
	make_test_queue (generic_q_push n q, n-1)


-- less repeated code
make_nf_test_group :: (String, (Queue, Int) -> [Int], Int) -> Benchmark
make_nf_test_group (s, f, n) =
	let listQ = make_test_queue (generic_q_make TList, n) in
	let strictQ = make_test_queue (generic_q_make TStrict, n) in
	let lazyQ = make_test_queue (generic_q_make TLazy, n) in
	let realtimeQ = make_test_queue (generic_q_make TRealTime, n) in
	bgroup s
		[ bench "list" $ nf f (listQ, 1000)
		, bench "strict" $ nf f (strictQ, 1000)
		, bench "lazy" $ nf f (lazyQ, 1000)
		, bench "realtime" $ nf f (realtimeQ, 1000)
		]

make_sized_array_test_group :: Int -> Benchmark
make_sized_array_test_group n = 
	bgroup (show n)
		[ make_nf_test_group ("test_pop_push", test_pop_push, n)
		, make_nf_test_group ("test_pop", test_pop, n)
		, make_nf_test_group ("test_push", test_push, n)
		, make_nf_test_group ("test_repeated_push_pop", test_repeated_push_pop, n)
		]



-- RUNNING TESTS
main = defaultMain [
	make_sized_array_test_group 1000,
	make_sized_array_test_group 10000,
	make_sized_array_test_group 100000
   ]
