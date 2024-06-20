# Multi-thread Example with Mutex

## 目標
這個專案旨在演示在多執行緒環境中使用 mutex 來避免 race condition。

## 結果

### 不使用 mutex 的版本
最終 balance 值可能不是 0，這是因為 race condition 導致的。

### 使用 mutex 的版本
最終 balance 值應該是 0，這是因為我們使用了 mutex 來保護對 `balance` 變數的訪問。

## 分析
在多執行緒程式中，不使用 mutex 會導致 race condition，因為多個執行緒會同時訪問和修改共享變數。使用 mutex 可以防止多個執行緒同時訪問共享變數，從而避免 race condition。
