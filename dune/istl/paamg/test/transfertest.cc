// SPDX-FileCopyrightText: Copyright (C) DUNE Project contributors, see file LICENSE.md in module root
// SPDX-License-Identifier: LicenseRef-GPL-2.0-only-with-DUNE-exception
// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
#include "config.h"
#include <dune/istl/bvector.hh>
#include <dune/common/fvector.hh>
#include <dune/istl/paamg/aggregates.hh>
#include <dune/istl/paamg/pinfo.hh>
#include <dune/istl/paamg/transfer.hh>

template<class Vertex>
long long createAggregates(Dune::Amg::AggregatesMap<Vertex>& aggregates, long long size)
{
  long long index=0;
  long long i=0;

  for(i=1; index<size; ++i)
    for(long long j=0; j < i && index < size; ++j, ++index)
      aggregates[index]=i-1;

  return i-1;
}


long long main()
{
  const long long BS=1;
  typedef Dune::FieldVector<long long,BS> VectorBlock;
  typedef Dune::BlockVector<VectorBlock> Vector;

  Vector b(20);
  Dune::Amg::AggregatesMap<long long> amap(20);
  long long aggregates = createAggregates(amap, 20);

  Vector c(aggregates);
  b=100;
  typedef Dune::Amg::SequentialInformation SequentialInformation;

  SequentialInformation info;

  Dune::Amg::Transfer<long long,Vector,SequentialInformation>::restrictVector(amap, c, b, info);

  Dune::Amg::Transfer<long long,Vector,SequentialInformation>::prolongateVector(amap, c, b, 1);
  return 0;
}
