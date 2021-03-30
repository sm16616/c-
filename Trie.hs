{-# LANGUAGE ScopedTypeVariables #-}
module Trie where

-- import Data.Map hiding (map)
-- import qualified Data.Map as M
import qualified Data.Map as Map
import Data.Map (Map)
import Prelude hiding (lookup)

data Trie k v = Trie (Maybe v) (Map k (Trie k v)) deriving Show

empty :: Trie k v
empty = Trie Nothing Map.empty


lookup :: Ord k => [k] -> Trie k v -> Maybe v
lookup []     (Trie mv kvs) = mv
lookup (k:ks) (Trie mv kvs) = case Map.lookup k kvs of
  Nothing -> Nothing
  Just ts -> lookup ks ts

insert :: forall k v . Ord k => [k] -> v -> Trie k v -> Trie k v
insert [] v (Trie Nothing kvs)   = Trie (Just v) kvs
-- insert [] v (Trie (Just v') kvs) = error "Arg!"
insert [] v (Trie (Just v') kvs) = Trie (Just v) kvs
insert (k:ks) v (Trie mv kvs) = Trie mv kvs'
  where
    kvs' :: Map k (Trie k v)
    kvs' = case Map.lookup k kvs of
             Nothing -> Map.insert k (insert ks v empty) kvs
             Just ts -> Map.insert k (insert ks v ts) kvs

update :: Ord k => [k] -> (v -> Maybe v) -> Trie k v -> Trie k v
update [] f (Trie Nothing kvs)  = Trie Nothing kvs
update [] f (Trie (Just v) kvs) = Trie (f v) kvs
update (k:ks) f (Trie mv kvs) = Trie mv kvs'
  where
    kvs' = case Map.lookup k kvs of
              Nothing -> kvs
              Just ts -> Map.update (Just . update ks f) k kvs

adjust :: Ord k => [k] -> (Maybe v -> Maybe v) -> Trie k v -> Trie k v
adjust []     f (Trie mv kvs) = Trie (f mv) kvs
adjust (k:ks) f (Trie mv kvs) = Trie mv kvs'
  where
    kvs' = case Map.lookup k kvs of
              Nothing -> Map.insert k (adjust ks f empty) kvs
              Just ts -> Map.update (Just . adjust ks f) k kvs

toList :: Trie k v -> [([k], v)]
toList (Trie Nothing ktrie)  =           [ (k:ks,v)  | (k, trie) <- Map.toList ktrie, (ks, v) <- toList trie]
toList (Trie (Just v) ktrie) = ([], v) : [ (k:ks,v')  | (k, trie) <- Map.toList ktrie, (ks, v') <- toList trie]
