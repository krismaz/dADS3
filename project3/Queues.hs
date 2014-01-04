module Queues where

--Implemented by following Gerths slides

list_q_make :: [Int]
list_q_make = []

list_q_inject :: Int -> [Int] -> [Int]
list_q_inject i l = reverse (i : (reverse l)) -- COuld probably be sped up by about a factor 2, depending on compiler magic

list_q_pop :: [Int] -> (Int, [Int])
list_q_pop (x:xs) = (x, xs)
list_q_pop [] = error "Empty list_q_pop"

strict_q_make :: ([Int], [Int])
strict_q_make = ([],[])

strict_q_inject :: Int -> ([Int], [Int]) -> ([Int], [Int])
strict_q_inject i (h, t) = (h, i:t)

strict_q_pop :: ([Int], [Int]) -> (Int, ([Int], [Int]))
strict_q_pop ([], []) = error "Empty strict_q_pop"
strict_q_pop ([], t) = strict_q_pop (reverse t,[])
strict_q_pop (h:hs, t) = (h, (hs, t))

lazy_q_make :: ([Int], [Int], (Int, Int))
lazy_q_make = ([],[], (0,0))

lazy_q_inject :: Int -> ([Int], [Int], (Int, Int)) -> ([Int], [Int], (Int, Int))
lazy_q_inject i (h, t, (lh, lt))
	| lh > lt = (h, i:t, (lh, lt + 1)) 
	| otherwise = (h ++ (reverse (i:t)), [] , (lh + lt + 1 , 0))

lazy_q_pop :: ([Int], [Int], (Int, Int)) -> (Int , ([Int], [Int], (Int, Int)))
lazy_q_pop ([], [], (0, 0)) = error "Empty lazy_q_pop" 
lazy_q_pop (h:hs, t, (lh, lt))
	| lh > lt = (h, (hs, t, (lh-1, lt))) --Note:slides work on different pattern match
	| otherwise = (h , (hs ++ (reverse (t)), [] , (lh + lt - 1 , 0)))


--Implemented by following Oskakis book on functional data structures

data State =
	Idle |
	Reversing !Int [Int] [Int] [Int] [Int] | 
	Appending !Int [Int] [Int] |
	Done [Int]

data MelvilleQ =
	Melville !Int  [Int] State !Int [Int]



melville_q_work :: State -> State
melville_q_work (Reversing !ok [] f' (y:ys) r') = (Appending ok f' (y:r'))
melville_q_work (Reversing !ok (f:fs) f' (r:rs) r') = (Reversing (ok+1) fs (f:f') rs (r:r'))
melville_q_work (Appending 0 f' r') = (Done r')
melville_q_work (Appending ok (f:f') r') = (Appending (ok-1) f' (f:r'))
melville_q_work state = state

melville_q_invalidate :: State -> State
melville_q_invalidate (Reversing !ok f f' r r') = (Reversing (ok-1) f f' r r') --strict parameters, very slight speedup, requires strict parameters
melville_q_invalidate (Appending 0 f' (r:r')) = (Done r')
melville_q_invalidate (Appending ok f' r') = (Appending (ok-1) f' r')
melville_q_invalidate state = state

melville_q_work2 :: MelvilleQ -> MelvilleQ
melville_q_work2 (Melville !lenf f state !lenr r) = case melville_q_work (melville_q_work state) of --Note, case is strict, but only in 1 layer
	(Done newf) -> (Melville lenf newf Idle lenr r)
	newstate -> (Melville lenf f newstate lenr r)

melville_q_check :: MelvilleQ -> MelvilleQ
melville_q_check (Melville lenf f state lenr r)
	| lenr <= lenf = melville_q_work2 (Melville lenf f state lenr r)
	| otherwise = melville_q_work2 (Melville (lenf + lenr) f (Reversing 0 f [] r []) 0 [])

melville_q_head :: MelvilleQ -> Int
melville_q_head (Melville !lenf [] state !lenr r) = error "Empty Melville pop"
melville_q_head (Melville !lenf (f:fs) state !lenr r) = f

melville_q_tail :: MelvilleQ -> MelvilleQ
melville_q_tail (Melville !lenf [] state !lenr r) = error "Empty Melville pop"
melville_q_tail (Melville !lenf (f:fs) state !lenr r) = melville_q_check (Melville (lenf-1) fs (melville_q_invalidate state) lenr r)

melville_q_make :: MelvilleQ
melville_q_make = (Melville 0 [] Idle 0 [])

melville_q_inject :: Int -> MelvilleQ -> MelvilleQ
melville_q_inject x (Melville !lenf f state !lenr r) = melville_q_check (Melville lenf f state (lenr + 1) (x:r))

melville_q_pop :: MelvilleQ -> (Int, MelvilleQ)
melville_q_pop q = (melville_q_head q, melville_q_tail q)

-- Easier Interfacing

data QType =
	TList |
	TStrict |
	TLazy |
	TRealTime

data Queue =
	List [Int] |
	Strict ([Int], [Int]) |
	Lazy ! ([Int], [Int],  (Int,  Int)) | 
	RealTime MelvilleQ


generic_q_make :: QType -> Queue
generic_q_make TList = (List list_q_make)
generic_q_make TStrict = (Strict strict_q_make)
generic_q_make TLazy = (Lazy lazy_q_make)
generic_q_make TRealTime = (RealTime melville_q_make)

generic_q_inject :: Int -> Queue -> Queue
generic_q_inject i (List l) = (List (list_q_inject i l))
generic_q_inject i (Strict p) = (Strict (strict_q_inject i p))
generic_q_inject i (Lazy pp) = (Lazy (lazy_q_inject i pp))
generic_q_inject i (RealTime m) = (RealTime (melville_q_inject i m))

generic_q_pop :: Queue -> (Int, Queue)
generic_q_pop (List l) = case (list_q_pop l) of
	(i, nl) -> (i, (List nl))
generic_q_pop (Strict p) = case (strict_q_pop p) of
	(i, np) -> (i, (Strict np))
generic_q_pop (Lazy pp) = case (lazy_q_pop pp) of
	     (i, npp) -> (i, (Lazy npp))
generic_q_pop (RealTime m) = case  (melville_q_pop m) of
	(i, nm) -> (i, (RealTime nm))