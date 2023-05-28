

const formatDateTime = (dateTimeStr) => {
    const dateTime = new Date(dateTimeStr);
    const year = dateTime.getFullYear();
    const month = String(dateTime.getMonth() + 1).padStart(2, '0');
    const day = String(dateTime.getDate()).padStart(2, '0');
    const hours = String(dateTime.getHours()).padStart(2, '0');
    const minutes = String(dateTime.getMinutes()).padStart(2, '0');
    
    const formattedDate = `${year}-${month}-${day} ${hours}:${minutes}`;
    return formattedDate;
  };
  
  
const getTime = (time) => {
      const hour = parseInt(time.split(" ")[1].split(":")[0]);
      if (hour >= 4 && hour <= 20) {
        return "day";
      } else {
        return "night";
      }
    };