Status Code (`std::int32_t`)
Value | Meaning
--- | ---
<0 | Failure
0 | Success
\>0 | Extended Success

Status codes should not be set/used in areas that should only fail as a result of a larger issue (the client database being corrupted, the input parameters not following preconditions (inferred or explicit), etc).
Preconditions should be documented if doing so would negate the use of error setting and would not complicate the caller.

- IPC:
  <br>Each transaction should contain a status code (`std::int32_t` unless there is a good reason to do otherwise), the meaning of which should be specified by an local enum.

- Internal (core or API):
  <br>In internal code, there is a global status enum containing all possible errors. The extended success section is reserved for individual functions, and may carry different meanings for each use case.

  - If a function returns non-void
    - If invalid return values exist
      <br>Pick one (use 0/-1 if convenient, then whatever works) to notify the caller of a failure.
      <br>On failure, return the value and set the error code accordingly.
      <br>On success, do not modify the error code, unless there are extended modes of success the caller should know about.

      <br>If all return values are valid, follow the rules of a function returning void.

  - If a function returns void:
    <br>Return the status code instead of setting it.
    <br>If there is a reason for that not being a good option (such as this being a non-void function with no invalid return values), then always set the status code regardless of execution.

- Checking status:
  <br>Check efficiently; the expected case should have a very fast execution path.
  <br>Usually, this means checking for a general case (success/failure) first, then narrowing down the result.

  <br>Errors do not have to be handled immediately, they can be passed on (as long as it is documented).

- `std` exceptions:
  <br>Exceptions are allowed for exceptional cases only and should be used _sparingly_.
  <br>They should be used in cases where a very rare (critical) failure can occur in which it is possible to recover from, or at least handle in some capacity.
  <br>Exceptions are used with the assumption that the implementation is zero-cost. If a common target cannot (does not?) use a zero-cost model, this stance may be reevaluated.
