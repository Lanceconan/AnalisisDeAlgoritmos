#programa: Busqueda Binaria

require 'date'
require 'Time'

class Bbinario
  
  #Variables de la clase
  @@operaciones = 0  
  @@tiemporFinalBusqueda = 0.00000000
  @@tiemporFinalOrdenamiento = 0.00000000
  #Llena el vector inicial manualmente
  def self.llenarManualmente(vector, num)
      i = 0
      loop do
         puts "Ingrese Numero #{i}"
         vector[i] = gets.chomp.to_i
         return vector if i == num
         i=i+1
      end
  end

  #Llenar aleatoriamente
  def self.llenarAleatorio(vector, num)
      
      i = 0      
      loop do         
         vector[i] = rand(999) + 1
         return vector if i == num
         i=i+1
      end
  end

  #Llenar en Orden no repetidos
  def self.llenarNoRepetidos(vector, num)
      
      i = 0
      loop do         
         vector[i] = i
         i=i+1
         return vector if i == num
         
      end
  end

# metodo de ordenamiento burbuja
  def self.ordenar(vector)
    
    inicio = Time.now
      for i in 0..vector.length-2
         for j in i+1...vector.length
             if vector[i] > vector[j]
                aux = vector[j]
                vector[j] = vector[i]
                vector[i] = aux
             end
         end
      end      
      termino = Time.now
      @@tiemporFinalOrdenamiento = termino - inicio
      return vector
  end

  #Mostrar en pantalla el vector generado y ordenado
  def self.imprimir(vector)
      vector.each do |i|
         print "|#{i}"
      end
      print "|"
  end

  # Se define la cantidad de entrada en el arreglo
  def self.getCantidad
    print "Ingrese Cantidad de Datos en el arreglo inicial: "
    STDOUT.flush
    cant = gets.chomp.to_i
    return cant
  end   
  
  # Se obtiene el valor a encontrar
  def self.getBuscado
    print "\n\nIngrese el numero a buscar: "
    STDOUT.flush
    cant = gets.chomp.to_i
    return cant
  end   

  # Algoritmo de busqueda binaria recursiva
  def self.busquedaBinariaRecursiva(vector, val, left, right)
    mid = (left + right) / 2    
    
    return -999 if left > right
 
    @@operaciones = @@operaciones + 1;
    
    if val == vector[mid]
      return mid 
    elsif val > vector[mid]
      busquedaBinariaRecursiva(vector, val, mid + 1, right)
    else
      busquedaBinariaRecursiva(vector, val, left, mid - 1)
    end
  end
 
  #Funcion donde se defie como y donde aplicar el algoritmo, con las condiciones entregadas por parametro
  def self.aplicarAlgoritmo(arreglo, cant)
    inicio = Time.now.to_f 
    ordenar(arreglo)
    termino = Time.now.to_f
    print "\n\nEl tiempo total empleado en el ordenamiento fue: "    
    orden = termino - inicio
    print  "%.7f Segundos" %(termino - inicio) 
    
    #Para numeros grandes deshabilitar mostrar el vector ordenado
    #puts "\nEl vector ingresado y ordenado fue"    
    #imprimir(arreglo)    
    
    buscado = getBuscado
    inicioU = Time.now.to_f 
    sleep(0.1)
    nuevo = busquedaBinariaRecursiva(arreglo,buscado,0,cant-1)
    terminoU = Time.now.to_f    
    busqueda = termino - inicio
    if nuevo == - 999
      puts "No se encontro el valor buscado, por lo tanto es el peor caso a evaluar"     
      print "\n\nLa cantidad de operaciones necesarias fueron: "
      print @@operaciones  
      print "\n\nEl tiempo de ejecucion total en la busqueda fue: "    
      print  "%.7f Segundos" %(terminoU - inicioU - 0.1)
      print "\n\nEl tiempo total empleado en la ejecucion: "    
      print  "%.7f Segundos" %((termino - inicio) + (terminoU - inicioU - 0.1))   
    
    else
      print "\nLa posicion del valor buscado en el arreglo inicial es: "
      print nuevo + 1
      print "\n\nLa cantidad de operaciones necesarias fueron: "
      print @@operaciones  
      print "\n\nEl tiempo total empleado en la busqueda fue: "    
      print  "%.7f Segundos" %(terminoU - inicioU - 0.1) 
      print "\n\nEl tiempo total empleado en la ejecucion: "    
      print  "%.7f Segundos" %((termino - inicio) + (terminoU - inicioU - 0.1))      
    end
  end
 
  # Funcion pricipal para ejecutar donde se definen los datos de entrada
  def self.principal
      arregloInicial = Array.new
      operacion = 0
      puts "================================================="
      puts "           Busqueda Binaria Recursiva"
      puts "            Con Ordenamiento Burbuja"
      puts "================================================="
      puts " "
      puts "Ingrese la opcion correspondiente"
      puts "1.- Poblar vector inicial con Numeros Correlativos Ordenados y no repetitivos"
      puts "2.- Poblar vector inicial Con Numeros aleatorios"
      puts "3.- Poblar vector inicial Manualmente "
      puts "X.- Cualquier otra opcion para salir"
      puts " "
      print "Ingrese Opcion: "
      STDOUT.flush
      opcion = gets.chomp.to_i
      if opcion == 1
        puts "Se poblara con Numeros Correlativos, no repetitivos"
        cantidad = getCantidad
        llenarNoRepetidos(arregloInicial, cantidad)
        aplicarAlgoritmo(arregloInicial, cantidad)
        
      elsif opcion == 2
        puts "Se poblara Con Numeros aleatorios"
        cantidad = getCantidad
        llenarAleatorio(arregloInicial, cantidad)        
        aplicarAlgoritmo(arregloInicial, cantidad)
      
      elsif opcion == 3
      puts "Se poblara Manualmente"
      cantidad = getCantidad
      llenarManualmente(arregloInicial, cantidad)
      aplicarAlgoritmo(arregloInicial, cantidad)
      
      else 
        puts "Se ingreso la Opcion Salir del Programa"
        puts "Programado en Ruby V 1.9.3"
        puts "Juan Cid Carrenio"
        puts "Manuel Irarrazabal"
        puts "Rafael Vivar"
        puts "Daniel Gutierrez"
        puts "Grupo Alias"
      end
  end

end

Bbinario.principal


