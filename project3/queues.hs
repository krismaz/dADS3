--Implemented by following Gerths slides

list_q_make :: [Integer]
list_q_make = []

list_q_push :: Integer -> [Integer] -> [Integer]
list_q_push i l = reverse (i : (reverse l))

list_q_pop :: [Integer] -> (Integer, [Integer])
list_q_pop (x:xs) = (x, xs)
list_q_pop [] = error "Empty list_q_pop"

strict_q_make :: ([Integer], [Integer])
strict_q_make = ([],[])

strict_q_push :: Integer -> ([Integer], [Integer]) -> ([Integer], [Integer])
strict_q_push i (h, t) = (h, i:t)

strict_q_pop :: ([Integer], [Integer]) -> (Integer, ([Integer], [Integer]))
strict_q_pop ([], []) = error "Empty strict_q_pop"
strict_q_pop ([], t) = strict_q_pop (reverse t,[])
strict_q_pop (h:hs, t) = (h, (hs, t))

lazy_q_make :: ([Integer], [Integer], (Integer, Integer))
lazy_q_make = ([],[], (0,0))

lazy_q_push :: Integer -> ([Integer], [Integer], (Integer, Integer)) -> ([Integer], [Integer], (Integer, Integer))
lazy_q_push i (h, t, (lh, lt))
	| lh > lt = (h, i:t, (lh, lt + 1)) 
	| otherwise = (h ++ (reverse (i:t)), [] , (lh + lt + 1 , 0))

lazy_q_pop :: ([Integer], [Integer], (Integer, Integer)) -> (Integer , ([Integer], [Integer], (Integer, Integer)))
lazy_q_pop ([], [], (0, 0)) = error "Empty lazy_q_pop" 
lazy_q_pop (h:hs, t, (lh, lt))
	| lh > lt = (h, (hs, t, (lh-1, lt)))
	| otherwise = (h , (hs ++ (reverse (t)), [] , (lh + lt - 1 , 0)))


--Implemented by following Oskakis book on functional data structures

data State =
	Idle |
	Reversing Integer [Integer] [Integer] [Integer] [Integer] |
	Appending Integer [Integer] [Integer] |
	Done [Integer]

data MelvilleQ =
	Melville Integer [Integer] State Integer [Integer]

melville_q_work :: State -> State
melville_q_work (Reversing ok [] f' (y:ys) r') = (Appending ok f' (y:r'))
melville_q_work (Reversing ok (f:fs) f' (r:rs) r') = (Reversing (ok+1) fs (f:f') rs (r:r'))
melville_q_work (Appending 0 f' r') = (Done r')
melville_q_work (Appending ok (f:f') r') = (Appending (ok-1) f' (f:r'))
melville_q_work state = state

melville_q_invalidate :: State -> State
melville_q_invalidate (Reversing ok f f' r r') = (Reversing (ok-1) f f' r r')
melville_q_invalidate (Appending 0 f' (r:r')) = (Done r')
melville_q_invalidate (Appending ok f' r') = (Appending (ok-1) f' r')
melville_q_invalidate state = state

melville_q_work2 :: MelvilleQ -> MelvilleQ
melville_q_work2 (Melville lenf f state lenr r) = case melville_q_work (melville_q_work state) of --Note, case is strict, but only in 1 layer
	(Done newf) -> (Melville lenf newf Idle lenr r)
	newstate -> (Melville lenf f newstate lenr r)

melville_q_check :: MelvilleQ -> MelvilleQ
melville_q_check (Melville lenf f state lenr r)
	| lenr <= lenf = melville_q_work2 (Melville lenf f state lenr r)
	| otherwise = melville_q_work2 (Melville (lenf + lenr) f (Reversing 0 f [] r []) 0 [])

melville_q_head :: MelvilleQ -> Integer
melville_q_head (Melville lenf [] state lenr r) = error "Empty Melville pop"
melville_q_head (Melville lenf (f:fs) state lenr r) = f

melville_q_tail :: MelvilleQ -> MelvilleQ
melville_q_tail (Melville lenf [] state lenr r) = error "Empty Melville pop"
melville_q_tail (Melville lenf (f:fs) state lenr r) = melville_q_check (Melville (lenf-1) fs (melville_q_invalidate state) lenr r)

melville_q_make :: MelvilleQ
melville_q_make = (Melville 0 [] Idle 0 [])

melville_q_push :: Integer -> MelvilleQ -> MelvilleQ
melville_q_push x (Melville lenf f state lenr r) = melville_q_check (Melville lenf f state (lenr + 1) (x:r))

melville_q_pop :: MelvilleQ -> (Integer, MelvilleQ)
melville_q_pop q = (melville_q_head q, melville_q_tail q)

-- Easier Interfacing

data QType =
	TList |
	TStrict |
	TLazy |
	TRealTime

data Queue =
	List [Integer] |
	Strict ([Integer], [Integer]) |
	Lazy ([Integer], [Integer], (Integer, Integer)) |
	RealTime MelvilleQ

generic_q_make:: QType -> Queue
generic_q_make TList = (List list_q_make)
generic_q_make TStrict = (Strict strict_q_make)
generic_q_make TLazy = (Lazy lazy_q_make)
generic_q_make TRealTime = (RealTime melville_q_make)

generic_q_push::Integer -> Queue -> Queue
generic_q_push i (List l) = (List (list_q_push i l))
generic_q_push i (Strict p) = (Strict (strict_q_push i p))
generic_q_push i (Lazy pp) = (Lazy (lazy_q_push i pp))
generic_q_push i (RealTime m) = (RealTime (melville_q_push i m))

generic_q_pop::Queue -> (Integer, Queue)
generic_q_pop (List l) = case (list_q_pop l) of
	(i, nl) -> (i, (List nl))
generic_q_pop (Strict p) = case (strict_q_pop p) of
	(i, np) -> (i, (Strict np))
generic_q_pop (Lazy pp) = case (lazy_q_pop pp) of
	     (i, npp) -> (i, (Lazy npp))
generic_q_pop (RealTime m) = case  (melville_q_pop m) of
	(i, nm) -> (i, (RealTime nm))