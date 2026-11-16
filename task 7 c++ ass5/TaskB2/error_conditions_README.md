# Error-condition tests
This program deliberately triggers negative-charge, above-cover, unknown-package, missing-record, invalid numeric text (`std::stod`) and `std::bad_alloc` paths. It also verifies a tracked object's destructor runs during exception unwinding. Run locally because memory allocation failure behaviour can vary by operating system and overcommit policy.
