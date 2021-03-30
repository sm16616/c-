module Fold where
import Prelude hiding (sum, product, length, and, or, all, any, filter, group,
transpose)

sum :: [Integer] -> Integer
sum = foldr (+) 0

product :: [Integer] -> Integer
product = foldr (*) 1

and :: [Bool] -> Bool
and = foldr (&&) True:

or :: [Bool] -> Bool
or = foldr (||) False

all :: (a -> Bool) -> [a] -> Bool
all f x = and (map f x)

some :: (a -> Bool) -> [a] -> Bool
some f x = or (map f x) -- or can do some p xs = foldr((||).p) False xs

length :: [a] -> Int
length xs = foldr f k xs where
  k = 0
  f n x = x + 1

filter :: (a -> Bool) -> [a] -> [a]
filter p xs = foldr f k xs where
  k = []
  f x xs = if p x then (x:xs)
     else xs

group :: Eq a => [a] -> [[a]]
group = foldr f k where
  k = []
  f x [] = [[x]]
  f x ((y:ys):yss)
    | x == y = (x:y:ys):yss
    | otherwise [x]:(y:ys):yss

transpose :: [[a]] -> [[a]]
transpose = foldr (zipwith (:)) (repeat [])
