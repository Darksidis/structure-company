# structure-company

## About
Graphic display (in the form of a ladder) of the OOP principle, the structure of companies is taken as an example.

## Structure

Departament
- manager (belongs to the worker class) 
- employees []
- sub-departments ['array of departments']

## ladder
department 1
--
  | manager
  ----
      | employees
      | ....
      |
      -- sub-departments
        | 
        | manager
        --
          | employees
          | ...
