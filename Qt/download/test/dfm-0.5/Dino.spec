%if 0%{?fedora} || 0%{?rhel_version} || 0%{?centos_version}
%define breq qt4-devel 
%define reqs qt qt-x11
%define qmake /usr/bin/qmake-qt4 
%define lrelease /usr/bin/lrelease-qt4 
%endif
%if 0%{?mandriva_version}
%define breq libqt4-devel qt4-linguist
%define reqs libqt4
%define qmake /usr/lib/qt4/bin/qmake
%define lrelease /usr/lib/qt4/bin/lrelease
%define qt4_translationdir /usr/lib/qt4/translations
%endif
%if 0%{?suse_version}  
%define breq libqt4-devel  
%define reqs libqt4 libqt4-x11 
%define qmake /usr/bin/qmake  
%define lrelease /usr/bin/lrelease  
%define _qt4_translationdir /usr/share/qt4/translations  
%endif


Name: dfm
Summary: Dino - Simple File Manager for GNU/Linux
Version: 0.5
Release: 5
License: GPL v3
Group: System/FileManager
BuildRoot: %{_tmppath}/build-root-%{name}
Source0: /usr/src/packages/SOURCES/dfm-%{version}.tar.gz
Packager: Denis Kv
Url: http://dfm.sf.net/
Vendor: Denis Kv

BuildRequires: gcc-c++, make,  python-devel, %{breq}
Requires: libc.so.6 libgcc_s.so.1 libgcc_s.so.1(GCC_3.0) libm.so.6 libpthread.so.0 libstdc++.so.6 libstdc++.so.6(CXXABI_1.3) libstdc++.so.6(GLIBCXX_3.4) %{reqs}     
%description
A simple file manager for GNU/Linux based on Qt.


%prep
rm -rf %{buildroot}
mkdir %{buildroot}

%setup -q

%build
mkdir -p %{buildroot}%{_datadir}/Dino
mkdir -p %{buildroot}%{_datadir}/Dino/bin
mkdir -p %{buildroot}%{_datadir}/Dino/bin/translations
mkdir -p %{buildroot}%{_datadir}/applications
%{qmake} Dino.pro 
make
%{lrelease} Dino.pro

%install
mkdir -p %{buildroot}%{_datadir}/Dino/bin
mkdir -p %{buildroot}%{_bindir}/
mkdir -p %{buildroot}%{_datadir}/Dino/bin/translations/
mkdir -p %{buildroot}%{_datadir}/Dino/
mkdir -p %{buildroot}%{_datadir}/applications/

cp -r Dino %{buildroot}%{_datadir}/Dino/bin
cp -r translations/Dino_*.qm %{buildroot}%{_datadir}/Dino/bin/translations/
cp -r dino.png %{buildroot}%{_datadir}/pixmaps/
cp -r dino.desktop %{buildroot}%{_datadir}/applications/

ln -sf %{_datadir}/Dino/bin/Dino %{buildroot}%{_bindir}/dino



%clean
rm -rf %{buildroot}

%files  
%defattr(-,root,root)  
%dir %{_bindir}
%dir %{_datadir}/Dino  
%dir %{_datadir}/Dino/bin
%dir %{_datadir}/Dino/bin/translations
%{_datadir}/applications/dino.desktop  
%{_datadir}/pixmaps/dino.png  
%{_datadir}/Dino/bin/Dino
%{_bindir}/dino
%{_datadir}/Dino/bin/translations/Dino_ru.qm 
%{_datadir}/Dino/bin/translations/Dino_de.qm
%{_datadir}/Dino/bin/translations/Dino_sr_RS.qm 
%{_datadir}/Dino/bin/translations/Dino_sr_BA.qm 
%{_datadir}/Dino/bin/translations/Dino_es_VE.qm 


%changelog
* Wed Feb 9 2012 Dino <denimnumber1@gmail.com> 0.2
- Added permission settings
- Added Make symlink func
