module Main where

import Prelude hiding (lookup)
import System.Environment
import Trie

main :: IO ()
main = do putStrLn "The awesome word counting machine"
          [filePath] <- getArgs
          file <- readFile filePath
          let trie = makeTrie (words file)
          enquire trie

enquire :: Trie Char Integer -> IO ()
enquire trie = do
  putStrLn "Which word do you want to count?"
  word <- getLine
  -- let x = count file word
  let x = lookup word trie
  putStrLn ("That word occurs: " ++ show x ++ " times.")
  enquire trie

count :: String -> String -> Int
count xs y = count' (words xs) y 0
  where
    count' :: [String] -> String -> Int -> Int
    count' []     y n = n
    count' (x:xs) y n
      | x == y    = count' xs y (n + 1)
      | otherwise = count' xs y n

makeTrie :: [String] -> Trie Char Integer
makeTrie xs = foldr f k xs where
  k :: Trie Char Integer
  k = empty

  f :: String -> Trie Char Integer -> Trie Char Integer
  f w trie = adjust w incr trie

incr :: Maybe Integer -> Maybe Integer
incr Nothing  = Just 1
incr (Just v) = Just (v + 1)
