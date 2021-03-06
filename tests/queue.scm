(import (rnrs)
        (mosh queue)
        (mosh test))

(let ([q (make-queue)])
  (test-true (queue-empty? q))
  (queue-push! q 1)
  (test-false (queue-empty? q))
  (test-eqv 1 (queue-pop! q))
  (test-true (queue-empty? q)))

(let ([q (make-queue)])
  (test-true (queue-empty? q))
  (queue-push! q 1)
  (queue-push! q 2)
  (test-false (queue-empty? q))
  (test-eqv 1 (queue-pop! q))
  (test-eqv 2 (queue-pop! q))
  (test-true (queue-empty? q)))

(let ([q (make-queue)])
  (test-true (queue-empty? q))
  (queue-push! q 1)
  (queue-push! q 2)
  (test-false (queue-empty? q))
  (test-eqv 1 (queue-pop! q))
  (queue-push! q 3)
  (test-eqv 2 (queue-pop! q))
  (test-eqv 3 (queue-pop! q))
  (test-true (queue-empty? q))
  (test-error error? (queue-pop! q)))

(let ([q1 (make-queue)]
      [q2 (make-queue)])
  (queue-push! q1 1)
  (queue-push! q1 2)
  (queue-push! q1 3)
  (queue-push! q2 4)
  (queue-push! q2 5)
  (queue-push! q2 6)
  (queue-append! q1 q2)
  (test-eqv 1 (queue-pop! q1))
  (test-eqv 2 (queue-pop! q1))
  (test-eqv 3 (queue-pop! q1))
  (test-eqv 4 (queue-pop! q1))
  (test-eqv 5 (queue-pop! q1))
  (test-eqv 6 (queue-pop! q1))
  (test-true (queue-empty? q1)))


(test-results)
