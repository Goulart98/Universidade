
import Data.Char
import Data.List

-- Questão 1 --

enumFromTo' :: Int -> Int -> [Int]
enumFromTo' 0 0 = []
enumFromTo' x y = if (x <= y)
                 then (x : (enumFromTo' (x+1) y))
                 else []


-- Questão 2 --

enumFromThenTo' :: Int -> Int -> Int -> [Int]
enumFromThenTo' 0 0 0 = []
enumFromThenTo' x y z 
               | x < y && x > z = []
               | x > y && x < z  = []
               | otherwise = x : enumFromThenTo' y (2*y-x) z


-- Questão 3 --

mm :: [Int] -> [Int] -> [Int]
mm [] [] = []
mm x y = x ++ y


-- Questão 4 --

pos :: [Int] -> Int -> Int
pos [] 0 = 0
pos (x:xs) y  
           | y == 0 = x
           | otherwise = pos xs (y-1)


-- Questão 5 --

reverse2 :: [Int] -> [Int]
reverse2 [] = []
reverse2 (x:xs) = (reverse2 xs) ++ [x]


-- Questão 6 --

take2 :: Int -> [Int] -> [Int]
take2 n [] = []
take2 n (x:xs) 
       |n == 0 = []
       |otherwise = x : take2 (n-1) xs


-- Questão 7 --

drop2 :: Int -> [Int] -> [Int]
drop2 n [] = []
drop2 n (x:xs)
           |n == 0 = (x:xs)
           |otherwise = drop2 (n-1) (xs)


-- Questão 8 -- 

zip2 :: [Int] -> [Int] -> [(Int,Int)]
zip2 l [] = []
zip2 [] l = []
zip2 (x:xs) (y:ys) = (x,y) : zip2 xs ys


-- Questão 9 --

elem2 :: Eq a => a -> [a] -> Bool
elem2 n [] = False
elem2 n (x:xs) 
           |n == x = True
           |otherwise = elem2 n xs


-- Questão 10 --

replicate2 :: Int -> a -> [a]
replicate2 0 a = []
replicate2 n x 
           | n == 1 = [x]
           | otherwise = x : replicate2 (n-1) x


-- Questão 11 --


intersperse2 :: a -> [a] -> [a]
intersperse2 a [] = []
intersperse2 a [x] = [x]
intersperse2 a (x:xs) = x:a: intersperse2 a xs 


-- Questão 12 -- 


--group2 :: Eq a => [a] -> [[a]]
--group2 [] = []
--group2 l = groupAux l : group2 ( (\\) l (groupAux l)) where


--groupAux [x] = [x]
--groupaux (x:y:xs) 
--           |y == x = x : groupAux (y:xs)
--           |otherwise = [x]


-- Questão 13 --

concat2 :: [[a]] -> [a]
concat2 [] = []
concat2 (x:xs) = x ++ concat2 xs


-- Questão 14 --

inits2 :: [a] -> [[a]]
inits2 [] = [[]]
inits2 l = reverse (initsAux2 l) where


initsAux [x] = []
initsAux (x:xs) = x : initsAux xs
initsAux2 [] = [[]]
initsAux2 l = (l : (initsAux2 (initsAux l)))


-- Questão 15 --

tails2 :: [a] -> [[a]]
tails2 [] = [[]]
tails2 l = (tailsAux2 l) where


tailsAux [x] = []
tailsAux (x:xs) = x : tailsAux xs
tailsAux2 [] = [[]]
tailsAux2 l = (l : (tailsAux2 (tailsAux l)))


--- Questão 16 --

isPrefixOf2 :: Eq a => [a] -> [a] -> Bool
isPrefixOf2 [] [] = True
isPrefixOf2 l [] = False
isPrefixOf2 [] l = True
isPrefixOf2 (x:xs) (y:ys) 
                    | (x==y) = isPrefixOf2 xs ys
                    | otherwise = False


-- Questão 17 -- 


--isSuffixOf2 :: Eq a => [a] -> [a] -> Bool
--isSuffixOf2 [] [] = False
--isSuffixOf2 l [] = True
--isSuffixOf2 [] l = False
--isSuffixOf2 (x:xs) (y:ys) 
--                    | (xs==ys) = isSuffixOf2 [x] [y]
--                    | otherwise = False


isSuffixOf2 :: Eq a => [a] -> [a] -> Bool
isSuffixOf2 l1 l2 = isPrefixOf2 (reverse l1) (reverse l2)


-- Questão 18 --

isSubsequenceOf2 :: Eq a => [a] -> [a] -> Bool
isSubsequenceOf2 [] [] = True
isSubsequenceOf2 l [] = False
isSubsequenceOf2 [] l = True
isSubsequenceOf2 (x:xs) (y:ys)
                    | x == y = isSubsequenceOf2 xs ys
                    | otherwise = isSubsequenceOf2 (x:xs) (ys)


-- Questão 19 --

--elemIndices2 :: Eq a => a -> [a] -> [Int]
--elemIndices2 n [] = []
--elemIndices2 n (x:xs)
--                   | (n==x) = (elemIndices2 n xs)


-- Questão 20 --

nub2 :: Eq a => [a] -> [a]
nub2 [] = []
nub2 (x:xs) = x : nub2 (nubAux x xs) where

nubAux x [] = []
nubAux x (y:ys) 
           | (x==y) = nubAux x ys
           | otherwise = y : (nubAux x ys)

-- Questão 21 -- 

delete2 :: Eq a => a -> [a] -> [a]
delete2 x [] = []
delete2 x (y:ys) 
            | (x==y) = ys
            | otherwise = y : (delete2 x ys)


-- Questão 22 --


elimina2 :: Eq a => [a] -> [a] -> [a]
elimina2 [] [] = []
elimina2 [] l = []
elimina2 l [] = l
elimina2 l (x:xs) = elimina2 (delete2 x l) xs


-- Questão 23 --

--union2 :: Eq a => [a] -> [a] -> [a] 
--union2 [] [] = []
--union2 [] l = l
--union2 l [] = l
--union2 (x:xs) (y:ys) 
--               | elem y (x:xs) = union2 (x:xs) ys
--               | otherwise = union2 (reverse2 (y:reverse2 (x:xs))) ys



-- Questão 24 --



intersect2 :: Eq a => [a] -> [a] -> [a]
intersect2 [] [] = []
intersect2 l [] = []
intersect2 [] l = []
intersect2 (x:xs) l
                  | elem x l = x : intersect2 xs l
                  | otherwise = intersect2 xs l



-- Questão 25 --


insert2 :: Ord a => a -> [a] -> [a]
insert2 n [] = [n]
insert2 x (y:ys) 
              | x <= y = (x:y:ys)
              | otherwise = y: (insert2 x ys)


-- Questão 26 --


unwords2 :: [String] -> String
unwords2 [] = []
unwords2 (x:xs) = x ++ [' '] ++ unwords2 xs



-- Questão 27 --


unlines2 :: [String] -> String
unlines2 [] = []
unlines2 (x:xs) = x ++ ['\n'] ++ unlines2 xs


-- Questão 28 --


pMaior2 :: Ord a => [a] -> Int
pMaior2 (x:xs) = pMaior2Aux 0 (maximum (x:xs)) (x:xs)   where
      pMaior2Aux y x  [] = y
      pMaior2Aux y x  (h:hs) | x == h = y 
                       | otherwise = pMaior2Aux (y+1) x hs



-- Questão 29 --

temRepetidos2 :: Eq a => [a] -> Bool
temRepetidos2 [] = False
temRepetidos2 (x:xs)
                   | elem x xs = True
                   | otherwise = temRepetidos2 xs


-- Questão 30 -- 

algarismos2 :: [Char] -> [Char]
algarismos2 [] = [] 
algarismos2 (x:xs) | (isDigit x) == True = x : algarismos2 (xs) 
                   | otherwise = algarismos2 xs 


-- Questão 31 --

posImpares :: [a] -> [a] 
posImpares [] = []
posImpares [x] = []
posImpares [x,y] = [y]
posImpares (x:y:xs) = y : posImpares xs


-- Questão 32 --

posPares :: [a] -> [a]
posPares [] = []
posPares [x] = [x]
posPares [x,y] = [x]
posPares (x:y:xs) = x : posPares xs


-- Questão 33 --


isSorted :: Ord a => [a] -> Bool
isSorted [] = True
isSorted [x] = True
isSorted (x:xs) | x > (head xs) = False
                | otherwise = isSorted xs



-- Questão 34 --




-- Questão 35 -- 

menor :: String -> String -> Bool
menor [] [] = False
menor l [] = False
menor [] l = True
menor (x:xs) (y:ys) | (toLower x) < (toLower y) = True
                    | (toLower x) > (toLower y) = False
                    | otherwise = menor xs ys 

-- Questão 44 --


data Movimento = Norte | Sul | Este | Oeste
                  deriving Show



posicao :: (Int,Int) -> [Movimento] -> (Int,Int)
posicao (x,y) [] = (x,y)
posicao (x,y) (Norte:ys) = posicao (x,y+1) ys 
posicao (x,y) (Sul:ys) = posicao (x,y-1) ys
posicao (x,y) (Este:ys) = posicao (x+1,y) ys
posicao (x,y) (Oeste:ys) = posicao (x-1,y) ys

-- Questão 45 --

caminho :: (Int,Int) -> (Int,Int) -> [Movimento]
caminho (0,0) (0,0) = []
caminho (x1,y1) (x2,y2) | x1 > x2 = Oeste : caminho (x1-1,y1) (x2,y2)
                        | x1 < x2 = Este : caminho (x1+1,y1) (x2,y2)
                        | y1 > y2 = Sul : caminho (x1,y1-1) (x2,y2)
                        | y1 < y2 = Norte : caminho (x1,y1+1) (x2,y2)
                        | otherwise = []


-- Questão 50 --

 data Semaforo = Verde | Amarelo | Vermelho
                   deriving Show


interseccaoOK :: [Semaforo] -> Bool
interseccaoOK [] = True
interseccaoOK (x:xs) | x == Verde = True
                     | x == Amarelo = True
                     | x == Vermelho = False
                     | otherwise =

















